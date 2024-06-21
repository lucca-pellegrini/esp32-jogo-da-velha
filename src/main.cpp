#include <Arduino.h>

#include "board.h"
#include "io.h"
#include "player.h"

static void boot_blink();

void setup()
{
	Serial.begin(115200);

	for (int i = 0; i < NUM_LEDS; ++i) {
		pinMode(greens[i], OUTPUT);
		pinMode(reds[i], OUTPUT);
	}
	pinMode(BTN1, INPUT);
	pinMode(BTN2, INPUT);

	boot_blink();
}

static void boot_blink()
{
	for (int i = 0; i < NUM_LEDS; ++i) {
		digitalWrite(reds[i], HIGH);
		delay(100);
	}
	for (int i = 0; i < NUM_LEDS; ++i) {
		digitalWrite(reds[i], LOW);
		digitalWrite(greens[i], HIGH);
		delay(100);
	}
	for (int i = 0; i < NUM_LEDS; ++i) {
		digitalWrite(greens[i], LOW);
		delay(100);
	}
	for (int i = 0; i < NUM_LEDS; i += 2)
		digitalWrite(reds[i], HIGH);
	delay(250);
	for (int i = 0; i < NUM_LEDS; ++i)
		digitalWrite(reds[i], LOW);
	for (int i = 1; i < NUM_LEDS; i += 2)
		digitalWrite(reds[i], HIGH);
	delay(250);
	for (int i = 0; i < NUM_LEDS; ++i)
		digitalWrite(reds[i], LOW);
	for (int i = 0; i < NUM_LEDS; i += 2)
		digitalWrite(greens[i], HIGH);
	delay(250);
	for (int i = 0; i < NUM_LEDS; ++i)
		digitalWrite(greens[i], LOW);
	for (int i = 1; i < NUM_LEDS; i += 2)
		digitalWrite(greens[i], HIGH);
	delay(250);
	for (int i = 0; i < NUM_LEDS; ++i)
		digitalWrite(greens[i], LOW);
}

void loop()
{
	char board[SIZE][SIZE]; // Tabuleiro (matriz).
	char cur_player; // Jogador atual.
	int game_mode = -1; // Modo de jogo (lido do usuário, abaixo).
	Difficulty difficulty = EASY; // Dificuldade (lida do usuário, abaixo).
	Difficulty difficulty2 = EASY; // Dificuldade do segundo computador.
	bool game_won; // Se o jogo terminou em vitória.
	bool game_draw; // Se o jogo terminou em empate.

	srand(time(NULL)); // Inicializa o estado interno da função `rand()`.

	// Inicializa todos os valores padrão.
	cur_player = 'X';
	game_won = false;
	game_draw = false;

	init_board(board); // Inicializa o tabuleiro.

	// Pede ao usuário que escolha um modo de jogo.
	do {
		Serial.println("Escolha um modo de jogo:");
		Serial.println("1. Jogador vs jogador");
		Serial.println("2. Jogador vs computador");
		Serial.println("3. Computador vs computador");
		while (Serial.available() == 0) {
		} // Espera o usuário digitar.
		game_mode = Serial.parseInt();
	} while (game_mode < 1 || game_mode > 3);

	// Caso escolha jogar contra o computador, decida quem jogará primeiro.
	if (game_mode == 2) {
		int primeiro = -1;
		do {
			Serial.println("\nQuem jogará primeiro?");
			Serial.println("1. Jogador");
			Serial.println("2. Computador");
			while (Serial.available() == 0) {
			} // Espera o usuário digitar.
			primeiro = Serial.parseInt();
		} while (primeiro < 1 || primeiro > 2);
		cur_player = (primeiro == 1) ? 'X' : 'O';
	}

	// Leia a dificuldade do computador.
	if (game_mode == 2 || game_mode == 3) {
		do {
			Serial.println("\nEscolha a dificuldade:");
			Serial.println("1. Fácil");
			Serial.println("2. Normal");
			Serial.println("3. Difícil");
			while (Serial.available() == 0) {
			} // Espera o usuário digitar.
			difficulty = static_cast<Difficulty>(Serial.parseInt());
		} while (difficulty < EASY || difficulty > HARD);
	}

	// Caso escolha assistir, leia a dificuldade do oponente.
	if (game_mode == 3) {
		do {
			Serial.println(
				"\nEscolha a dificuldade para o oponente:");
			Serial.println("1. Fácil");
			Serial.println("2. Normal");
			Serial.println("3. Difícil");
			while (Serial.available() == 0) {
			} // Espera o usuário digitar.
			difficulty2 =
				static_cast<Difficulty>(Serial.parseInt());
		} while (difficulty2 < EASY || difficulty2 > HARD);
	}

	// Itera até o jogo estar terminado.
	while (!game_won && !game_draw) {
		print_board(board); // Mostra o tabuleiro.

		// Determina se o próximo jogador é um usuário ou o computador.
		if (game_mode == 2 && cur_player == 'O') {
			Serial.println("O computador está jogando…");
			cpu_move(board, cur_player, difficulty);
		} else if (game_mode == 3) {
			Serial.println("O computador está jogando…");
			if (cur_player == 'X')
				cpu_move(board, cur_player, difficulty);
			else
				cpu_move(board, cur_player, difficulty2);
			delay(2000);
		} else {
			bool move_confirmed = false;
			int cursor_pos = -1;
			move_cursor(&cursor_pos, board);
			while (!move_confirmed) {
				delay(200);
				flash_cursor(cursor_pos, cur_player);
				if (is_button_pressed(BTN1)) {
					Serial.println("Apertou botão 1");
					move_cursor(&cursor_pos, board);
					delay(500); // Debounce delay
				}
				if (is_button_pressed(BTN2)) {
					Serial.println("Apertou botão 2");
					int row = cursor_pos / SIZE;
					int col = cursor_pos % SIZE;
					if (make_move(board, row, col,
						      cur_player)) {
						move_confirmed = true;
					} else {
						Serial.println(
							"Jogada inválida. Tente novamente.");
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
	} else if (game_draw) {
		Serial.println("Empate!");
	}

}
