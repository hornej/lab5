/*
 * ticTacToeDisplay.c
 *
 *  Created on: Oct 18, 2016
 *      Author: hornej2
 */

#include "ticTacToeDisplay.h"
#include "minimax.h"
#include "../interval_timers/buttons.h"
#include "../switches_buttons_lab/switches.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "supportFiles/display.h"
#include "supportFiles/utils.h"

#define DISPLAY_ONE_THIRD_WIDTH DISPLAY_WIDTH/3 //one-third display width
#define DISPLAY_TWO_THIRD_WIDTH DISPLAY_WIDTH/3*2 //two-thirds display width
#define DISPLAY_ONE_THIRD_HEIGHT DISPLAY_HEIGHT/3 //one-third display width
#define DISPLAY_TWO_THIRD_HEIGHT DISPLAY_HEIGHT/3*2 //two-thirds display width
#define DISPLAY_TOP 0 //y coordinate for top of display
#define DISPLAY_LEFT 0 //x coordinate for left of display
#define DISPLAY_BOTTOM DISPLAY_HEIGHT //y coordinate for bottom of display
#define DISPLAY_RIGHT DISPLAY_WIDTH //x coordinate for right of display
#define DISPLAY_ONE_SIXTH_WIDTH DISPLAY_WIDTH/6 //one sixth of display width
#define DISPLAY_ONE_SIXTH_HEIGHT DISPLAY_HEIGHT/6 //one sixth of display height
#define RADIUS_O DISPLAY_WIDTH/12 //radius of O
#define DISPLAY_TWELVETH_WIDTH DISPLAY_WIDTH/12 //one twelveth of the display width
#define TIME_DELAY 50 //wait for screen to initialize
#define TEXT_SIZE 10 //set the text size

#define TOP 0 //top row
#define MIDDLE 1 //middle row
#define BOTTOM 2 //bottom row
#define LEFT 0 //left column
#define CENTER 1 //center column
#define RIGHT 2 //right column

#define BUTTON_0_ADDR 1 //address of BTN0
#define BUTTON_1_ADDR 2 //address of BTN1
#define SWITCH_0_ADDR 1 //address of SW0s

// Inits the tic-tac-toe display, draws the lines that form the board.
void ticTacToeDisplay_init(){
    //display_init(); //initialize the display
    //switches_init(); //initialize the switches
    //buttons_init(); //initialize the buttons
    display_fillScreen(DISPLAY_BLACK); //initialize the display to be black
    ticTacToeDisplay_drawBoardLines(); //draw the tic tac toe board
}

// Draws an X at the specified row and column.
// erase == true means to erase the X by redrawing it as background. erase == false, draw the X as foreground.
void ticTacToeDisplay_drawX(uint8_t row, uint8_t column, bool erase){
    //setting the 4 x,y coordinates necessary to draw an X
    //The X will display at the coordinate corresponding with the row and column touched
    uint16_t x0 = (DISPLAY_ONE_THIRD_WIDTH*column) + DISPLAY_ONE_SIXTH_WIDTH - DISPLAY_TWELVETH_WIDTH;
    uint16_t y0 = (DISPLAY_ONE_THIRD_HEIGHT*row) + DISPLAY_ONE_SIXTH_HEIGHT - DISPLAY_TWELVETH_WIDTH;
    uint16_t x1 = (DISPLAY_ONE_THIRD_WIDTH*column) + DISPLAY_ONE_SIXTH_WIDTH + DISPLAY_TWELVETH_WIDTH;
    uint16_t y1 = (DISPLAY_ONE_THIRD_HEIGHT*row) + DISPLAY_ONE_SIXTH_HEIGHT + DISPLAY_TWELVETH_WIDTH;
    uint16_t x2 = (DISPLAY_ONE_THIRD_WIDTH*column) + DISPLAY_ONE_SIXTH_WIDTH - DISPLAY_TWELVETH_WIDTH;
    uint16_t y2 = (DISPLAY_ONE_THIRD_HEIGHT*row) + DISPLAY_ONE_SIXTH_HEIGHT + DISPLAY_TWELVETH_WIDTH;
    uint16_t x3 = (DISPLAY_ONE_THIRD_WIDTH*column) + DISPLAY_ONE_SIXTH_WIDTH + DISPLAY_TWELVETH_WIDTH;
    uint16_t y3 = (DISPLAY_ONE_THIRD_HEIGHT*row) + DISPLAY_ONE_SIXTH_HEIGHT - DISPLAY_TWELVETH_WIDTH;
    if (!erase){ //draw a green X
        display_drawLine(x0,y0,x1,y1,DISPLAY_GREEN);
        display_drawLine(x2,y2,x3,y3,DISPLAY_GREEN);
    }
    else { //erase by drawing a black X
        display_drawLine(x2,y2,x3,y3,DISPLAY_BLACK);
    }
}

// Draws an O at the specified row and column.
// erase == true means to erase the X by redrawing it as background. erase == false, draw the X as foreground.
void ticTacToeDisplay_drawO(uint8_t row, uint8_t column, bool erase){
    //setting the x,y coordinate for the center of the O
    //the O will display at the coordinate corresponding with the row and column touched
    uint16_t x = (DISPLAY_ONE_THIRD_WIDTH*column) + DISPLAY_ONE_SIXTH_WIDTH;
    uint16_t y = (DISPLAY_ONE_THIRD_HEIGHT*row) + DISPLAY_ONE_SIXTH_HEIGHT;
    if (!erase){ //draw a green O
        display_drawCircle(x,y,RADIUS_O,DISPLAY_GREEN);
    }
    else { //erase by drawing a black O
        display_drawCircle(x,y,RADIUS_O,DISPLAY_BLACK);
    }
}

// After a touch has been detected and after the proper delay, this sets the row and column arguments
// according to where the user touched the board.
void ticTacToeDisplay_touchScreenComputeBoardRowColumn(uint8_t* row, uint8_t* column){
    int16_t x; //x coordinate
    int16_t y; //y coordinate
    uint8_t z; //pressure (will not be needed)
    display_getTouchedPoint(&x, &y, &z); // Returns the x-y coordinate point and the pressure (z).

    if (y < DISPLAY_ONE_THIRD_HEIGHT){ //top row
        *row = TOP;
    }
    if (y > DISPLAY_ONE_THIRD_HEIGHT && y < DISPLAY_TWO_THIRD_HEIGHT){ //midddle row
        *row = MIDDLE;
    }
    if (y > DISPLAY_TWO_THIRD_HEIGHT){ //bottom row
        *row = BOTTOM;
    }
    if (x < DISPLAY_ONE_THIRD_WIDTH){ //left column
        *column = LEFT;
    }
    if (x > DISPLAY_ONE_THIRD_WIDTH && x < DISPLAY_TWO_THIRD_WIDTH){ //center column
        *column = CENTER;
    }
    if (x > DISPLAY_TWO_THIRD_WIDTH){ //right column
        *column = RIGHT;
    }
}

// Runs a test of the display. Does the following.
// Draws the board. Each time you touch one of the screen areas, the screen will paint
// an X or an O, depending on whether switch 0 (SW0) is slid up (O) or down (X).
// When BTN0 is pushed, the screen is cleared. The test terminates when BTN1 is pushed.
void ticTacToeDisplay_runTest(){
    uint8_t row;
    uint8_t column;
    while(true){
        if (display_isTouched()){ //if the display is touched
            display_clearOldTouchData(); //clear the touch data
            utils_msDelay(TIME_DELAY); //let it settle
            ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row,&column); //figure out where the board was touched
            if (switches_read() & SWITCH_0_ADDR){ //if SW0 is up draw an O
                ticTacToeDisplay_drawO(row,column,false); //draw O
            }
            else {
                ticTacToeDisplay_drawX(row,column,false); //if SW0 is down draw X
            }
        }
        else if (buttons_read() & BUTTON_0_ADDR){ //when btn0 is pushed
            display_fillScreen(DISPLAY_BLACK); //display screen black
            ticTacToeDisplay_drawBoardLines(); //redraw the tic tac toe board
        }
        else if (buttons_read() & BUTTON_1_ADDR){ //when btn1 is pushed
            display_fillScreen(DISPLAY_BLACK); //display screen black
            display_setCursor(DISPLAY_TOP,DISPLAY_LEFT); //set cursor at top left screen
            display_setTextColor(DISPLAY_RED); //set red text color
            display_setTextSize(TEXT_SIZE); //text size
            display_println("GAME OVER"); //write GAME OVER on board
            break;
        }
    }
}

// This will draw the four board lines.
void ticTacToeDisplay_drawBoardLines(){
    //draw left line
    display_drawLine(DISPLAY_ONE_THIRD_WIDTH,DISPLAY_TOP,DISPLAY_ONE_THIRD_WIDTH,DISPLAY_BOTTOM,DISPLAY_GREEN);
    //draw right line
    display_drawLine(DISPLAY_TWO_THIRD_WIDTH,DISPLAY_TOP,DISPLAY_TWO_THIRD_WIDTH,DISPLAY_BOTTOM,DISPLAY_GREEN);
    //draw top line
    display_drawLine(DISPLAY_LEFT,DISPLAY_ONE_THIRD_HEIGHT,DISPLAY_RIGHT,DISPLAY_ONE_THIRD_HEIGHT,DISPLAY_GREEN);
    //draw bottom line
    display_drawLine(DISPLAY_LEFT,DISPLAY_TWO_THIRD_HEIGHT,DISPLAY_RIGHT,DISPLAY_TWO_THIRD_HEIGHT,DISPLAY_GREEN);
}


