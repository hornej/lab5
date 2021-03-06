/*
 * minimax.h
 *
 *  Created on: Oct 6, 2016
 *      Author: hornej2
 */

#ifndef MINIMAX_H_
#define MINIMAX_H_

#include <stdint.h>
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


// Boards contain just an array of squares. I used a struct to provide additional abstraction
// in case I wanted to add something to the board type.
typedef struct {
    uint8_t squares[MINIMAX_BOARD_ROWS][MINIMAX_BOARD_COLUMNS];  // State of game as passed in.
} minimax_board_t;

// A move is simply a row-column pair.
typedef struct {
    uint8_t row;
    uint8_t column;
} minimax_move_t;

// Define a score type.
typedef int16_t minimax_score_t;

// This routine is not recursive but will invoke the recursive minimax function.
// It computes the row and column of the next move based upon:
// the current board,
// the player. true means the computer is X. false means the computer is O.
void minimax_computeNextMove(minimax_board_t* board, bool player_is_x, uint8_t* row, uint8_t* column);

// Determine that the game is over by looking at the score.
bool minimax_isGameOver(minimax_score_t score);

// Returns the score of the board, based upon the player and the board.
// This returns one of 4 values: MINIMAX_PLAYER_WINNING_SCORE,
// MINIMAX_OPPONENT_WINNING_SCORE, MINIMAX_DRAW_SCORE, MINIMAX_NOT_ENDGAME
// Note: the player argument makes it possible to speed up this function.
// Assumptions:
// (1) if player_is_x == true, the last thing played was an 'X'.
// (2) if player_is_x == false, the last thing played was an 'O'.
// Hint: If you know the game was not over when an 'X'was played,
// you don't need to look for 'O's, and vice-versa.
minimax_score_t minimax_computeBoardScore(minimax_board_t* board, bool player_is_x);

// Init the board to all empty squares.
void minimax_initBoard(minimax_board_t* board);

#endif /* MINIMAX_H_ */
