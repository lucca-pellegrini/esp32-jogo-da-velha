#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "board.h" // Para as definições do tabuleiro.
#include "player.h" // Para as jogadas do computador.

int main(void)
{
	char board[SIZE][SIZE]; // Tabuleiro (matriz).
	char cur_player; // Jogador atual.
	int game_mode = -1; // Modo de jogo (lido do usuário, abaixo).
	Difficulty difficulty = -1; // Dificuldade (lida do usuário, abaixo).
	Difficulty difficulty2 = -1; // Dificuldade do segundo computador.
	bool game_won; // Se o jogo terminou em vitória.
	bool game_draw; // Se o jogo terminou em empate.
	char rematch; // Se o usuário vai querer repetir o jogo.

	srand(time(NULL)); // Inicializa o estado interno da função `rand()`.

begin: // Rótulo de começo de jogo, caso o usuário queira jogar de novo.

	// Inicializa todos os valores padrão.
	cur_player = 'X';
	game_won = false;
	game_draw = false;
	rematch = '\0';

	init_board(board); // Inicializa o tabuleiro.

	// Pede ao usuário que escolha um modo de jogo.
	do {
		printf("Escolha um modo de jogo:\n");
		printf("1. Jogador vs jogador\n");
		printf("2. Jogador vs computador\n");
		printf("3. Computador vs computador\n");
		printf("Digite a sua escolha: ");
		scanf("%d", &game_mode);
	} while (game_mode < 1 || game_mode > 3);

	// Caso escolha jogar contra o computador, decida quem jogará primeiro.
	if (game_mode == 2) {
		int primeiro = -1;
		do {
			printf("\nQuem jogará primeiro?\n");
			printf("1. Jogador\n");
			printf("2. Computador\n");
			printf("Digite a sua escolha: ");
			scanf("%d", &primeiro);
		} while (primeiro < 1 || primeiro > 2);
		cur_player = (primeiro == 1) ? 'X' : 'O';
	}

	// Leia a dificuldade do computador.
	if (game_mode == 2 || game_mode == 3) {
		do {
			printf("\nEscolha a dificuldade:\n");
			printf("1. Fácil\n");
			printf("2. Normal\n");
			printf("3. Difícil\n");
			printf("Digite a sua escolha: ");
			scanf("%d", &difficulty);
		} while (difficulty < EASY || difficulty > HARD);
	}

	// Caso escolha assistir, leia a dificuldade do oponente.
	if (game_mode == 3) {
		do {
			printf("\nEscolha a dificuldade para o oponente:\n");
			printf("1. Fácil\n");
			printf("2. Normal\n");
			printf("3. Difícil\n");
			printf("Digite a sua escolha: ");
			scanf("%d", &difficulty2);
		} while (difficulty2 < EASY || difficulty2 > HARD);
	}

	// Itera até o jogo estar terminado.
	while (!game_won && !game_draw) {
		int row, col;
		print_board(board); // Mostra o tabuleiro.

		// Determina se o próximo jogador é um usuário ou o computador.
		if (game_mode == 2 && cur_player == 'O') {
			printf("O computador está jogando…\n");
			cpu_move(board, cur_player, difficulty);
		} else if (game_mode == 3) {
			printf("O computador está jogando…\n");
			if (cur_player == 'X')
				cpu_move(board, cur_player, difficulty);
			else
				cpu_move(board, cur_player, difficulty2);
			sleep(2);
		} else {
			printf("Jogador “%c”, digite a sua jogada "
			       "(linha e coluna): ",
			       cur_player);
			scanf("%d %d", &row, &col);

			// Faz a jogada digitada, mas verifica se foi inválida.
			if (!make_move(board, row - 1, col - 1, cur_player)) {
				printf("Jogada inválida. Tente novamente.\n");
				continue;
			}
		}

		// Verifica o estado do jogo.
		game_won = check_win(board, cur_player);
		game_draw = check_draw(board);

		if (!game_won) // Se ninguém ganhou, troca o jogador atual.
			cur_player = (cur_player == 'X') ? 'O' : 'X';
	}

	print_board(board); // Mostra o tabuleiro ao final do jogo.

	// Mostra a mensagem de jogo apropriada.
	if (game_won) {
		printf("Jogador “%c” ganhou!\n", cur_player);
	} else if (game_draw) {
		printf("Empate!\n");
	}

	// Pergunta ao usuário se ele quer jogar de novo.
	do {
		printf("\nJogar de novo? (responda ‘S’ ou ‘N’): ");
		scanf(" %c", &rematch);
		rematch = toupper(rematch);
	} while (rematch != 'S' && rematch != 'N');

	// Se o usuário respondeu que sim, volta ao rótulo `begin`, acima.
	if (rematch == 'S') {
		printf("Reiniciando o jogo…\n\n");
		goto begin;
	}

	return 0;
}