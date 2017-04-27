/*
 * ticTacToeControl.c
 *
 *  Created on: Oct 20, 2016
 *      Author: hornej2
 */

#include <stdio.h>
#include <stdbool.h>
#include "string.h"
#include "ticTacToeControl.h"
#include "ticTacToeDisplay.h"
#include "supportFiles/display.h"
#include "supportFiles/utils.h"
#include "minimax.h"
#include "../interval_timers/buttons.h"

#define RESET 0 //resets counters
#define MINIMAX_USED_SQUARE 3           // Used when creating new board states.
#define MINIMAX_PLAYER_SQUARE 2    // player-square means X occupies the square.
#define MINIMAX_OPPONENT_SQUARE 1  // opponent-square means O occupies the square.
#define MINIMAX_EMPTY_SQUARE 0 //0 signifies an empty square
#define ADC_MAX 1 //max count for adc
#define CNT_MAX 15 //max count for cnt
#define BUTTON_0_ADDR 1 //address for pressing BTN0
#define DISPLAY_TOP 0 //y coordinate for top of display
#define DISPLAY_LEFT 0 //x coordinate for left of display

minimax_board_t board; //the tic tac toe board of rows and columns
bool player; //determines if player is x or not
bool erase; //bool to erase or draw the board
uint8_t row0; //row number of the board
uint8_t column0; //column number of the board
uint32_t adc; //adc counter
uint32_t cnt; //cnt counter
bool valid; //bool to see if valid move or not
bool X = false; //sets player to X which is false

// States for the controller state machine.
enum ticTacToeControl_st_t {
    init_st, // Start here, stay in this state for just one tick.
    start_st, //stay in this state to decide if computer or human goes first
    adc_first_st, //check to see if its a real touch
    adc_running_st, //stay in this stay to decide whos turn it is
    write_computer_st, //write the computer move and draw the board
    computer_first_st,
    wait_player_st, //wait for human to play
    write_player_st, //write the human player move and draw the board
    end_game_st, //stay in this state when the game is won
    clear_display_st //when button is pushed clear diplay and start over
} currentState = init_st; //start in the init_st

static ticTacToeControl_st_t previousState;
static bool firstPass = true;

// This is a debug state print routine. It will print the names of the states each
// time tick() is called. It only prints states if they are different than the
// previous state.
void debugStatePrint() {
    // Only print the message if:
    // 1. This the first pass and the value for previousState is unknown.
    // 2. previousState != currentState - this prevents reprinting the same state name over and over.
    if (previousState != currentState || firstPass) {
        firstPass = false;                // previousState will be defined, firstPass is false.
        previousState = currentState;     // keep track of the last state that you were in.
        switch(currentState) {            // This prints messages based upon the state that you were in.
        case init_st:
            printf("init_st\n\r"); //print init_st to console
            break;
        case start_st:
            printf("start_st\n\r"); //print start_st to console
            break;
        case adc_first_st:
            printf("adc_first_st\n\r"); //print adc_first_st to console
            break;
        case adc_running_st:
            printf("adc_running_st\n\r"); //print adc_running_st to console
            break;
        case write_computer_st:
            printf("write_computer_st\n\r");  //print write_computer_st to console
            break;
        case computer_first_st:
            printf("computer_first_st\n\r"); //print computer_first_st to console
            break;
        case wait_player_st:
            printf("wait_player_st\n\r"); //print wait_player_st to console
            break;
        case write_player_st:
            printf("write_player_st\n\r"); //print write_player_st to console
            break;
        case end_game_st:
            printf("end_game_st\n\r"); //print end_game_st to console
            break;
        case clear_display_st:
            printf("clear_display_st\n\r"); //print clear_display_st to console
            break;
        }
    }
}

void ticTacToeControl_tick() {
    debugStatePrint();

    // Perform state action first
    switch(currentState) {
    case init_st:
        adc=RESET; //set adc counter to 0
        cnt=RESET; //set cnt counter to 0

        //ticTacToeDisplay_init(); //initialize the tic tac toe display
        break;
    case start_st:
        cnt++; //increment cnt
        break;
    case adc_first_st:
        adc++; //increment adc
        break;
    case adc_running_st:
        adc++; //increment adc
        break;
    case write_computer_st:
        //have the computer compute the next move it should play to potentially win
        minimax_computeNextMove(&board,player,&row0,&column0);
        if (player){ //if the computer is X draw an X in the desired square
            board.squares[row0][column0]=MINIMAX_PLAYER_SQUARE; //save an X to the board
            ticTacToeDisplay_drawX(row0,column0,erase); //draw an X on the screen
        }
        else { //if the computer is O draw an O in the desired square
            board.squares[row0][column0]=MINIMAX_OPPONENT_SQUARE; //save an O to the board
            ticTacToeDisplay_drawO(row0,column0,erase); //draw an O on the screen
        }
        break;
    case computer_first_st: //if computer plays first it will always be top left corner
        board.squares[DISPLAY_LEFT][DISPLAY_TOP]=MINIMAX_PLAYER_SQUARE; //save an X to the board
        ticTacToeDisplay_drawX(DISPLAY_LEFT,DISPLAY_TOP,erase); //draw an X on the screen
        break;
    case wait_player_st: //no state action
        break;
    case write_player_st:
        //have the touch screen compute to where the player has touched
        ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row0,&column0);
        valid = !board.squares[row0][column0]; //if the square is empty it will be a valid play
        if (!player && valid){ //if the human player is X and touched in a valid square draw an X
            board.squares[row0][column0]=MINIMAX_PLAYER_SQUARE; //save an X to the board
            ticTacToeDisplay_drawX(row0,column0,erase); //draw an X on the screen
        }
        else if (player && valid){ //if the human player is O and touched in a valid square draw O
            board.squares[row0][column0]=MINIMAX_OPPONENT_SQUARE; //save an O to the board
            ticTacToeDisplay_drawO(row0,column0,erase); //draw an O on the screen
        }
        break;
    case end_game_st: //no state action
        break;
    case clear_display_st:
        cnt=RESET; //set cnt counter to 0
        adc=RESET; //set adc counter to 0
        for (uint32_t row = RESET; row < MINIMAX_BOARD_ROWS; row++){ //go through rows
            for (uint32_t column = RESET; column < MINIMAX_BOARD_COLUMNS; column++){ //go through columns
                if(board.squares[row][column]!=MINIMAX_EMPTY_SQUARE){ //if the square is not empty
                    ticTacToeDisplay_drawO(row,column,!erase); //erase all Os
                    ticTacToeDisplay_drawX(row,column,!erase); //erase all Xs
                }
            }
        }
        minimax_initBoard(&board); //clear the tic tac toe board
        break;
    default:
        printf("ticTacToeControl_tick state update: hit default\n\r");
        break;
    }
    // Perform state update next
    switch(currentState) {
    case init_st:
        currentState = start_st; //move to the start_st
        break;
    case start_st:
        if (cnt < CNT_MAX){ //if the cnt is less than CNT_MAX stay in start_st
            currentState = start_st; //stay in start_st
        }
        if (!display_isTouched() && cnt==CNT_MAX){ //if the human doesnt play the computer will start

            player = !X; //computer is going to start as X
            currentState = computer_first_st; //go to write_computer_st
        }
        if (display_isTouched()){ //if the human touches the screen before the cnt, they will play as X first
            adc=RESET; //clear the adc counter to 0
            currentState = adc_first_st; //move to adc_first_st
        }
        break;
    case adc_first_st:
        if (adc < CNT_MAX){ //if adc is less than CNT_MAX stay in the adc_start_st
            currentState = adc_first_st; //stay in adc_first_st
        }
        if (!display_isTouched() && adc==ADC_MAX){ //if display is not touched and adc=ADC+MAX
            cnt=cnt+ADC_MAX; //increment cnt
            currentState = start_st; //go back to start_st
        }
        if (display_isTouched() && adc==ADC_MAX){ //if the display is touched and adc=ADC_MAX
            player = X;
            currentState = wait_player_st; //go to wait_player_st
        }
        break;
    case adc_running_st:
        if (adc < ADC_MAX){ //if adc is less than ADC_MAX
            currentState = adc_running_st; //go to adc_running_st
        }
        if (display_isTouched() && adc==ADC_MAX){ //if the display is touched and adc=ADC_MAX
            currentState = write_player_st; //go to write_player_st
        }
        if (!display_isTouched() && adc==ADC_MAX){ //if the display is not touched and adc=ADC_MAX
            currentState = wait_player_st; //go to wait_player_st. wait until the player touches a square
        }
        break;
    case write_computer_st:
        if(!minimax_isGameOver(minimax_computeBoardScore(&board,!player))){ //if the game is not over yet
            currentState = wait_player_st; //wait for the human to play
        }
        else {
            currentState = end_game_st; //if not, end the game
        }
        break;
    case computer_first_st:
        currentState = wait_player_st; //go to wait_player_st
        break;
    case wait_player_st:
        if (display_isTouched()){ //once the display is touched
            adc=RESET; //reset the adc counter to 0
            display_clearOldTouchData(); //clear the old touch data to settle
            currentState = adc_running_st; //go to adc_running_st
        }
        if (!display_isTouched()){ //if the display is not touched
            currentState = wait_player_st; //countinue to wait for player to stay
        }
        break;
    case write_player_st:
        if (!valid){ //if the humans square is not valid
            currentState = wait_player_st; //continue waiting for them to play a valid square
        }
        //if they play a valid square and the game is over
        if (valid && minimax_isGameOver(minimax_computeBoardScore(&board,!player))){
            currentState = end_game_st; //end the game
        }
        //if they player a valid square and the game is not over
        if (valid && !minimax_isGameOver(minimax_computeBoardScore(&board,!player))){
            currentState = write_computer_st; //computer will play next
        }
        break;
    case end_game_st:
        if (buttons_read() & BUTTON_0_ADDR){ //if BTN0 is pressed
            currentState = clear_display_st; //clear the display
        }
        else {
            currentState = end_game_st; //wait here until BTN0 is pressed
        }
        break;
    case clear_display_st:
        currentState = start_st; //go back to start_st
        break;
    default:
        printf("ticTacToeControl_tick state action: hit default\n\r");
        break;
    }
}


