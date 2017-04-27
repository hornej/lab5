/*
 * minimax.c
 *
 *  Created on: Oct 6, 2016
 *      Author: hornej2
 */

#include <stdio.h>
#include <stdint.h>
#include "minimax.h"

#define TOP 0 //top row
#define MIDDLE 1 //middle row
#define BOTTOM 2 //bottom row
#define LEFT 0 //left column
#define CENTER 1 //center column
#define RIGHT 2 //right column

#define X true
#define O false

// Defines the boundaries of the tic-tac-toe board.
#define MINIMAX_BOARD_ROWS 3
#define MINIMAX_BOARD_COLUMNS 3

// These are the values in the board to represent who is occupying what square.
#define MINIMAX_USED_SQUARE 3           // Used when creating new board states.
#define MINIMAX_PLAYER_SQUARE 2    // player-square means X occupies the square.
#define MINIMAX_OPPONENT_SQUARE 1  // opponent-square means O occupies the square.
#define MINIMAX_EMPTY_SQUARE 0

// Scoring for minimax.
#define MINIMAX_PLAYER_WINNING_SCORE 10     // This means that X will win.
#define MINIMAX_OPPONENT_WINNING_SCORE -10  // This means that O will win.
#define MINIMAX_DRAW_SCORE 0                // Nobody wins.
#define MINIMAX_NOT_ENDGAME -1              // Not an end-game.
#define MINIMAX_BOARD_SIZE 9 //size of the board

#define ZERO 0 //the number 0. good for initializing stuff
minimax_move_t choice;

// player_is_x = true -> X, player_is_x = false -> O
int minimax(minimax_board_t* board, bool player_is_x) {
    minimax_score_t globalScore = minimax_computeBoardScore(board,player_is_x);
    uint8_t tracker = ZERO;
    minimax_move_t moves[MINIMAX_BOARD_SIZE];
    minimax_score_t scores[MINIMAX_BOARD_SIZE];
    if (minimax_isGameOver(globalScore)){
        // Recursion base case, there has been a win or a draw.
        // If game is over, you need to evaluate board based upon previous player/opponent.
        return globalScore;
    }
    else {
        // Otherwise, you need to recurse.
        // This loop will generate all possible boards.
        for (uint32_t row = ZERO; row < MINIMAX_BOARD_ROWS; row++) {
            for (uint32_t column = ZERO; column < MINIMAX_BOARD_COLUMNS; column++) {
                if(board->squares[row][column] == MINIMAX_EMPTY_SQUARE) {
                    // Assign the square to the player or opponent.
                    if (player_is_x)
                        board->squares[row][column] = MINIMAX_PLAYER_SQUARE;
                    else
                        board->squares[row][column] = MINIMAX_OPPONENT_SQUARE;

                    globalScore = minimax(board,!player_is_x);
                    scores[tracker] = globalScore; //add score to move-score table
                    moves[tracker].row = row;  //add move to move-score table
                    moves[tracker].column = column;
                    // Undo the change to the board (return the square to empty) prior to next iteration of for-loops.
                    board->squares[row][column] = MINIMAX_EMPTY_SQUARE;
                    tracker++;
                }
            }
        }
    }
    // Once you get here, you have iterated over empty squares at this level. All of the scores have been computed
    // in the move-score table for boards at this level.
    // Now you need to return the score depending upon whether you are computing min or max.
    globalScore = scores[MINIMAX_EMPTY_SQUARE];
    choice = moves[MINIMAX_EMPTY_SQUARE];
    if (player_is_x) {
        for(uint32_t i = ZERO; i < tracker; i++){
            if(scores[i] >= globalScore){
                globalScore = scores[i];
                choice = moves[i];
            }
        }
    } else {
        for(uint32_t i = ZERO; i < tracker; i++){
            if(scores[i] <= globalScore){
                globalScore = scores[i];
                choice = moves[i];
            }
        }
    }
    return globalScore;
}


// This routine is not recursive but will invoke the recursive minimax function.
// It computes the row and column of the next move based upon:
// the current board,
// the player. true means the computer is X. false means the computer is O.
void minimax_computeNextMove(minimax_board_t* board, bool player, uint8_t* row, uint8_t* column){
    minimax(board, player); //call minimax function
    *row = choice.row; //save the choice to row pointer
    *column = choice.column; //save the choice to column pointer
    return;
}

// Determine that the game is over by looking at the score.
bool minimax_isGameOver(minimax_score_t score){
    if (score == MINIMAX_NOT_ENDGAME){
        return false; //if not over return false
    }
    else{
        return true; //if over return true
    }
}

// Returns the score of the board, based upon the player and the board.
// This returns one of 4 values: MINIMAX_PLAYER_WINNING_SCORE,
// MINIMAX_OPPONENT_WINNING_SCORE, MINIMAX_DRAW_SCORE, MINIMAX_NOT_ENDGAME
// Note: the player argument makes it possible to speed up this function.
// Assumptions:
// (1) if player == true, the last thing played was an 'X'.
// (2) if player == false, the last thing played was an 'O'.
// Hint: If you know the game was not over when an 'X' was played,
// you don't need to look for 'O's, and vice-versa.
minimax_score_t minimax_computeBoardScore(minimax_board_t* board, bool player){
    uint32_t playerNumber;
    if (player == !X){ //if the player is X
        playerNumber = MINIMAX_PLAYER_SQUARE; //save to board as X
    }
    else {
        playerNumber = MINIMAX_OPPONENT_SQUARE; //if player is O save to board as O
    }
    uint32_t winningScore;
    if (player == !X){ //if player is X
        winningScore = MINIMAX_PLAYER_WINNING_SCORE; //the winning score is 10
    }
    else {
        winningScore = MINIMAX_OPPONENT_WINNING_SCORE; //if player is O the winning score is -10
    }

    //check for diagonal wins
    if(
            (board->squares[TOP][LEFT]==playerNumber &&
                    board->squares[MIDDLE][CENTER]==playerNumber &&
                    board->squares[BOTTOM][RIGHT]==playerNumber) ||

                    (board->squares[TOP][RIGHT]==playerNumber &&
                            board->squares[MIDDLE][CENTER]==playerNumber &&
                            board->squares[BOTTOM][LEFT]==playerNumber)
    ) //if there is a diagonal win
    {
        return winningScore; //return the appropriate winning score if found
    }

    //check for vertical wins
    if(
            (board->squares[TOP][LEFT]==playerNumber &&
                    board->squares[MIDDLE][LEFT]==playerNumber &&
                    board->squares[BOTTOM][LEFT]==playerNumber) ||

                    (board->squares[TOP][RIGHT]==playerNumber &&
                            board->squares[MIDDLE][RIGHT]==playerNumber &&
                            board->squares[BOTTOM][RIGHT]==playerNumber) ||

                            (board->squares[TOP][CENTER]==playerNumber &&
                                    board->squares[MIDDLE][CENTER]==playerNumber &&
                                    board->squares[BOTTOM][CENTER]==playerNumber)
    )//if there is a vertical win
    {
        return winningScore; //return the appropriate winning score if found
    }

    //check for horizontal wins
    if(
            (board->squares[TOP][LEFT]==playerNumber &&
                    board->squares[TOP][RIGHT]==playerNumber &&
                    board->squares[TOP][CENTER]==playerNumber) ||

                    (board->squares[MIDDLE][LEFT]==playerNumber &&
                            board->squares[MIDDLE][RIGHT]==playerNumber &&
                            board->squares[MIDDLE][CENTER]==playerNumber) ||

                            (board->squares[BOTTOM][LEFT]==playerNumber &&
                                    board->squares[BOTTOM][RIGHT]==playerNumber &&
                                    board->squares[BOTTOM][CENTER]==playerNumber)
    ) //if there is a horizontal win
    {
        return winningScore; //return the appropriate winning score if found
    }

    //check for empty squares

    for (uint32_t row = ZERO; row < MINIMAX_BOARD_ROWS; row++){ //go through rows
        for (uint32_t column = ZERO; column < MINIMAX_BOARD_COLUMNS; column++){ //go through columns
            if(board->squares[row][column]==MINIMAX_EMPTY_SQUARE){ //if the square is empty
                return MINIMAX_NOT_ENDGAME; //the game is not over
            }
        }
    }

    // else draw

    return MINIMAX_DRAW_SCORE;
}

// Init the board to all empty squares.
void minimax_initBoard(minimax_board_t* board){
    for (uint32_t row = ZERO; row < MINIMAX_BOARD_ROWS; row++){ //go through rows
        for (uint32_t column = ZERO; column < MINIMAX_BOARD_COLUMNS; column++){ //go through columns
            board->squares[row][column]=MINIMAX_EMPTY_SQUARE; //clear all squares
        }
    }
}
