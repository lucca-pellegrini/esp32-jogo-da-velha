#pragma once // Garante que esse arquivo não será incluído mais de uma vez.

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"

// Dificuldades para modos de jogo diferentes.
typedef enum { EASY = 1, NORMAL = 2, HARD = 3 } Difficulty;

void cpu_move(char board[SIZE][SIZE], char player, Difficulty difficulty);

#ifdef __cplusplus
}
#endif
