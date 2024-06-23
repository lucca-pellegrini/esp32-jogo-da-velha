#include <Arduino.h>

#include <time.h>

#include "board.h"
#include "io.h"
#include "player.h"
#include "settings.h"

void setup()
{
	for (int i = 0; i < NUM_LEDS; ++i) {
		pinMode(greens[i], OUTPUT);
		pinMode(reds[i], OUTPUT);
	}
	pinMode(BTN1, INPUT);
	pinMode(BTN2, INPUT);

	srand(time(NULL)); // Inicializa o estado interno da função `rand()`.

	boot_blink();
	set_sm();
	modal_setup();
}

void loop()
{
	// Configurações de jogo padrão.
	Options opt = { .game_mode = 2,
			.difficulty = NORMAL,
			.difficulty2 = NORMAL,
			.first = Options::PLAYER };
	char board[SIZE][SIZE]; // Tabuleiro (matriz).
	char cur_player; // Jogador atual.
	bool game_won = false; // Se o jogo terminou em vitória.
	bool game_draw = false; // Se o jogo terminou em empate.

	init_board(board); // Inicializa o tabuleiro.
	get_settings(&opt); // Recebe as configurações.

	// Determina jogador atual baseado em quem jogará primeiro.
	cur_player = (opt.first == Options::PLAYER) ? 'X' : 'O';

	// Itera até o jogo estar terminado.
	while (!game_won && !game_draw) {
		print_board(board); // Mostra o tabuleiro.

		// Determina se o próximo jogador é um usuário ou o computador.
		if (opt.game_mode == 2 && cur_player == 'O') {
			Serial.println("O computador está jogando…");
			delay(1000);
			cpu_move(board, cur_player, opt.difficulty);
		} else if (opt.game_mode == 3) {
			Serial.println("O computador está jogando…");
			delay(1000);
			if (cur_player == 'X')
				cpu_move(board, cur_player, opt.difficulty);
			else
				cpu_move(board, cur_player, opt.difficulty2);
			delay(2000);
		} else {
			bool move_confirmed = false;
			int cursor_pos = -1;
			move_cursor(&cursor_pos, board);
			delay(1000);
			while (!move_confirmed) {
				if (check_and_handle_bt() == RETURN)
					return;
				delay(200);
				flash_cursor(cursor_pos, cur_player);
				if (is_button_pressed(BTN1)) {
					move_cursor(&cursor_pos, board);
					delay(500); // Debounce delay
				}
				if (is_button_pressed(BTN2)) {
					int row = cursor_pos / SIZE;
					int col = cursor_pos % SIZE;
					if (make_move(board, row, col,
						      cur_player)) {
						move_confirmed = true;
					}
					delay(500); // Debounce delay
				}
			}
			print_led_board(board);
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
		Serial.print("Jogador “");
		Serial.print(cur_player);
		Serial.println("” ganhou!");
		announce_victory(cur_player);
		delay(1500);
		blink_winner(cur_player, board);
	} else if (game_draw) {
		Serial.println("Empate!");
		delay(1500);
		blink_draw(board);
	}
}
