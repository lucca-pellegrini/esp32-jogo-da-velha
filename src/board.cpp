#include <Arduino.h>

#include <stdbool.h>

#include "board.h"
#include "io.h"

// Inicializa o tabuleiro.
void init_board(char board[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			board[i][j] = ' ';
}

// Mostra o tabuleiro
void print_board(char board[SIZE][SIZE])
{
	Serial.println();
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			Serial.print(" ");
			Serial.print(board[i][j]);
			Serial.print(" ");
			if (j < SIZE - 1)
				Serial.print("|");
		}
		Serial.println();
		if (i < SIZE - 1) {
			for (int j = 0; j < SIZE; ++j) {
				Serial.print("---");
				if (j < SIZE - 1)
					Serial.print("+");
			}
			Serial.println();
		}
	}
	Serial.println();

	// Atualiza o tabuleiro de LEDs
	print_led_board(board);
}

// Faz a jogada do `jogador` nas coordenadas passadas. Retorna se é válida.
bool make_move(char board[SIZE][SIZE], int row, int col, char player)
{
	if (row >= 0 && row < SIZE && col >= 0 && col < SIZE &&
	    board[row][col] == ' ') {
		board[row][col] = player;
		return true;
	}
	return false;
}

// Verifica se o `jogador` ganhou.
bool check_win(char board[SIZE][SIZE], char player)
{
	// Verifica as linhas e as colunas.
	for (int i = 0; i < SIZE; ++i) {
		if ((board[i][0] == player && board[i][1] == player &&
		     board[i][2] == player) ||
		    (board[0][i] == player && board[1][i] == player &&
		     board[2][i] == player)) {
			return true;
		}
	}

	// Verifica as diagonais.
	if ((board[0][0] == player && board[1][1] == player &&
	     board[2][2] == player) ||
	    (board[0][2] == player && board[1][1] == player &&
	     board[2][0] == player))
		return true;

	// Se não encontramos condição de vitória, retorna `false`.
	return false;
}

// Verifica se foi empate. Note: não reconhece vitória.
bool check_draw(char board[SIZE][SIZE])
{
	// Se encontrarmos algum espaço vazio, não é empate.
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if (board[i][j] == ' ')
				return false;

	// Caso contrário, é empate.
	return true;
}
