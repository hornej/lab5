/*
 * main.c
 *
 *  Created on: Oct 6, 2016
 *      Author: hornej2
 */

#include "minimax.h"
#include <stdio.h>
#include <stdint.h>

int main() {
    minimax_board_t board1;  // Board 1 is the main example in the web-tutorial that I use on the web-site.
    board1.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board1.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board1.squares[0][2] = MINIMAX_PLAYER_SQUARE;
    board1.squares[1][0] = MINIMAX_PLAYER_SQUARE;
    board1.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board1.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board1.squares[2][0] = MINIMAX_PLAYER_SQUARE;
    board1.squares[2][1] = MINIMAX_OPPONENT_SQUARE;
    board1.squares[2][2] = MINIMAX_OPPONENT_SQUARE;

    minimax_board_t board2;
    board2.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board2.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board2.squares[0][2] = MINIMAX_PLAYER_SQUARE;
    board2.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board2.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board2.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board2.squares[2][0] = MINIMAX_PLAYER_SQUARE;
    board2.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board2.squares[2][2] = MINIMAX_OPPONENT_SQUARE;

    minimax_board_t board3;
    board3.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board3.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board3.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board3.squares[1][0] = MINIMAX_OPPONENT_SQUARE;
    board3.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board3.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board3.squares[2][0] = MINIMAX_PLAYER_SQUARE;
    board3.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board3.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board4;
    board4.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board4.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board4.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board4.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board4.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board4.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board4.squares[2][0] = MINIMAX_PLAYER_SQUARE;
    board4.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board4.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board5;
    board5.squares[0][0] = MINIMAX_PLAYER_SQUARE;
    board5.squares[0][1] = MINIMAX_PLAYER_SQUARE;
    board5.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board5.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board5.squares[1][1] = MINIMAX_OPPONENT_SQUARE;
    board5.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board5.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board5.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board5.squares[2][2] = MINIMAX_EMPTY_SQUARE;

    minimax_board_t board6;
    board6.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board6.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board6.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board6.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board6.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board6.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board6.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board6.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board6.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board7;
    board7.squares[0][0] = MINIMAX_PLAYER_SQUARE;
    board7.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board7.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board7.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board7.squares[1][1] = MINIMAX_OPPONENT_SQUARE;
    board7.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board7.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board7.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board7.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board8;
    board8.squares[0][0] = MINIMAX_PLAYER_SQUARE;
    board8.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board8.squares[0][2] = MINIMAX_OPPONENT_SQUARE;
    board8.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board8.squares[1][1] = MINIMAX_OPPONENT_SQUARE;
    board8.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board8.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board8.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board8.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board9;
    board9.squares[0][0] = MINIMAX_EMPTY_SQUARE;
    board9.squares[0][1] = MINIMAX_OPPONENT_SQUARE;
    board9.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board9.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board9.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board9.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board9.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board9.squares[2][1] = MINIMAX_PLAYER_SQUARE;
    board9.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board10;
    board10.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board10.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board10.squares[0][2] = MINIMAX_OPPONENT_SQUARE;
    board10.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board10.squares[1][1] = MINIMAX_PLAYER_SQUARE;
    board10.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board10.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board10.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board10.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board11;
    board11.squares[0][0] = MINIMAX_EMPTY_SQUARE;
    board11.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board11.squares[0][2] = MINIMAX_OPPONENT_SQUARE;
    board11.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board11.squares[1][1] = MINIMAX_PLAYER_SQUARE;
    board11.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board11.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board11.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board11.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board12;
    board12.squares[0][0] = MINIMAX_EMPTY_SQUARE;
    board12.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board12.squares[0][2] = MINIMAX_PLAYER_SQUARE;
    board12.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board12.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board12.squares[1][2] = MINIMAX_PLAYER_SQUARE;
    board12.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board12.squares[2][1] = MINIMAX_OPPONENT_SQUARE;
    board12.squares[2][2] = MINIMAX_OPPONENT_SQUARE;

    minimax_board_t board13;
    board13.squares[0][0] = MINIMAX_EMPTY_SQUARE;
    board13.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board13.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board13.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board13.squares[1][1] = MINIMAX_OPPONENT_SQUARE;
    board13.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board13.squares[2][0] = MINIMAX_PLAYER_SQUARE;
    board13.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board13.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board14;
    board14.squares[0][0] = MINIMAX_PLAYER_SQUARE;
    board14.squares[0][1] = MINIMAX_OPPONENT_SQUARE;
    board14.squares[0][2] = MINIMAX_PLAYER_SQUARE;
    board14.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board14.squares[1][1] = MINIMAX_EMPTY_SQUARE;
    board14.squares[1][2] = MINIMAX_OPPONENT_SQUARE;
    board14.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board14.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board14.squares[2][2] = MINIMAX_EMPTY_SQUARE;

    minimax_board_t board15;
    board15.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board15.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board15.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board15.squares[1][0] = MINIMAX_EMPTY_SQUARE;
    board15.squares[1][1] = MINIMAX_PLAYER_SQUARE;
    board15.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board15.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board15.squares[2][1] = MINIMAX_EMPTY_SQUARE;
    board15.squares[2][2] = MINIMAX_PLAYER_SQUARE;

    minimax_board_t board16;
    board16.squares[0][0] = MINIMAX_OPPONENT_SQUARE;
    board16.squares[0][1] = MINIMAX_EMPTY_SQUARE;
    board16.squares[0][2] = MINIMAX_EMPTY_SQUARE;
    board16.squares[1][0] = MINIMAX_OPPONENT_SQUARE;
    board16.squares[1][1] = MINIMAX_PLAYER_SQUARE;
    board16.squares[1][2] = MINIMAX_EMPTY_SQUARE;
    board16.squares[2][0] = MINIMAX_EMPTY_SQUARE;
    board16.squares[2][1] = MINIMAX_PLAYER_SQUARE;
    board16.squares[2][2] = MINIMAX_OPPONENT_SQUARE;


    minimax_board_t board17;
    board17.squares[0][0] = MINIMAX_OPPONENT_SQUARE;//upper left corner
    board17.squares[0][1] =MINIMAX_OPPONENT_SQUARE; //bottom right
    board17.squares[0][2] = MINIMAX_EMPTY_SQUARE; //bottom right
    board17.squares[1][0] = MINIMAX_PLAYER_SQUARE; //middle //bottom right
    board17.squares[1][1] = MINIMAX_PLAYER_SQUARE; //middle
    board17.squares[1][2] = MINIMAX_OPPONENT_SQUARE; //middle
    board17.squares[2][0] = MINIMAX_OPPONENT_SQUARE;//upper left corner
    board17.squares[2][1] = MINIMAX_EMPTY_SQUARE; //middle
    board17.squares[2][2] = MINIMAX_PLAYER_SQUARE; //bottom right


    uint8_t row, column;
    minimax_computeNextMove(&board1, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board1: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board2, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board2: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board3, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board3: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board4, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board4: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board5, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board5: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board6, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board6: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board7, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board7: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board8, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board8: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board9, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board9: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board10, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board10: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board11, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board11: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board12, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board12: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board13, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board13: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board14, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board14: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board15, false, &row, &column);
    printf("player is:%d\n\r",false);
    printf("next move for board15: (%d, %d)\n\n\n\r", row, column);
    minimax_computeNextMove(&board16, true, &row, &column);
    printf("player is:%d\n\r",true);
    printf("next move for board16: (%d, %d)\n\n\n\r", row, column);
    printf("player is:%d\n\r",true);
    minimax_computeNextMove(&board17, true, &row, &column);
    printf("next move for board17: (%d, %d)\n\n\n\r", row, column);
}

void isr_function() {
    // Empty for now.
}
