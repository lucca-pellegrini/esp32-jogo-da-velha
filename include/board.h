#pragma once // Garante que esse arquivo não será incluído mais de uma vez.

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/* Dimensões do tabuleiro. Se esse valor não for igual a 3, o jogo ainda
 * funcionará, mas não será possível jogar nas dificuldades mais altas. */
#define SIZE 3

void init_board(char board[SIZE][SIZE]);
void print_board(char board[SIZE][SIZE]);
bool make_move(char board[SIZE][SIZE], int row, int col, char player);
bool check_win(char board[SIZE][SIZE], char player);
bool check_draw(char board[SIZE][SIZE]);

#ifdef __cplusplus
}
#endif
