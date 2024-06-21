#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "player.h"

// Protótipos das funções internas deste arquivo.
static void easy_move(char board[SIZE][SIZE], char player);
static void medium_move(char board[SIZE][SIZE], char player);
static void hard_move(char board[SIZE][SIZE], char player);
static int minimax(char board[SIZE][SIZE], bool is_maximizing, char player,
		   char opponent);

// Função pública. Recebe a dificuldade e invoca o procedimento adequado.
void cpu_move(char board[SIZE][SIZE], char player, Difficulty difficulty)
{
	switch (difficulty) {
	case EASY:
		easy_move(board, player);
		break;
	case NORMAL:
		medium_move(board, player);
		break;
	case HARD:
		hard_move(board, player);
		break;
	default: // Dificuldade inválida.
		fprintf(stderr, "Erro: %s recebeu dificuldade inválida\n",
			__func__); // Mensagem de erro.
		assert(false); // Crasha o programa.
	}
}

// Modo fácil: jogada aleatória.
static void easy_move(char board[SIZE][SIZE], char player)
{
	int row, col;
	do { // Loop garante jogada válida.
		row = rand() % SIZE;
		col = rand() % SIZE;
	} while (!make_move(board, row, col, player));
}

// Modo normal: evita erros graves e toma oportunidade de ganhar.
static void medium_move(char board[SIZE][SIZE], char player)
{
	char opponent = (player == 'X') ? 'O' : 'X'; // Quem é o oponente.

	// Verifica se alguma jogada nos faz ganhar imediatamente.
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] != ' ')
				continue;

			board[i][j] = player;
			if (check_win(board, player))
				return;
			board[i][j] = ' ';
		}
	}

	// Bloqueia jogada do oponente que o faria ganhar, se existir.
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] != ' ')
				continue;

			board[i][j] = opponent;
			if (check_win(board, opponent)) {
				board[i][j] = player;
				return;
			}
			board[i][j] = ' ';
		}
	}

	// Caso contrário, faz uma jogada aleatória.
	easy_move(board, player);
}

// Modo difícil: Usa minimax para determinar a melhor jogada possível.
static void hard_move(char board[SIZE][SIZE], char player)
{
	char opponent = (player == 'X') ? 'O' : 'X'; // Quem é o oponente.
	int best_score = INT_MIN; // Melhor resultado possível. (1, 0, ou -1.)
	int best_row = -1, best_col = -1; // Coordenadas da melhor jogada.

	// Itera sobre cada espaço no tabuleiro.
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			// Se não for espaço vazio, ignoramos.
			if (board[i][j] != ' ')
				continue;

			// Para cada jogada, determina a pontuação com minimax.
			board[i][j] = player;
			int score = minimax(board, false, player, opponent);
			board[i][j] = ' '; // Com a pontuação, desfaz a jogada.

			/* Se for melhor, atualiza as coordenadas. Atualizamos
			 * também se a avaliação for igual, com probabilidade
			 * de 50%. */
			if (score > best_score ||
			    (score == best_score && rand() % 2)) {
				best_score = score;
				best_row = i;
				best_col = j;
			}
		}
	}

	// Executa a melhor jogada, que determinamos com o minimax.
	make_move(board, best_row, best_col, player);
}

/*
 * Função auxiliar recursiva: para identificar a melhor jogada com um dado
 * estado no tabuleiro, usamos minimax para determinar se a posição atual
 * resulta em vitória, derrota, ou empate, se todos jogarem perfeitamente. Os
 * parâmetros `player` e `opponent` serão 'X' ou 'O'. Função adaptada de um dos
 * exemplos em pseudocódigo encontrados em:
 * <https://books.google.com.br/books?id=cb0qEAAAQBAJ>.
 * Veja também: <https://pt.wikipedia.org/wiki/Minimax>.
 */
static int minimax(char board[SIZE][SIZE], bool is_maximizing, char player,
		   char opponent)
{
	// Inicializa com o menor/maior valor, dependendo do modo de operação.
	int best_score = is_maximizing ? INT_MIN : INT_MAX;

	// Caso de parada: o jogo já terminou.
	if (check_win(board, player))
		return 1;
	if (check_win(board, opponent))
		return -1;
	if (check_draw(board))
		return 0;

	// Itera sobre cada espaço no tabuleiro.
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			// Se não for espaço vazio, ignoramos.
			if (board[i][j] != ' ')
				continue;

			// Faz a jogada para o dado modo de operação.
			board[i][j] = is_maximizing ? player : opponent;

			// Faz a chamada recursiva, determinando a pontuação.
			int score = minimax(board, !is_maximizing, player,
					    opponent);
			board[i][j] = ' '; // Com a pontuação, desfaz a jogada.

			// Se for melhor, atualiza `best_score`.
			best_score = is_maximizing ? fmax(best_score, score) :
						     fmin(best_score, score);
		}
	}

	// Retorna o resultado.
	return best_score;
}