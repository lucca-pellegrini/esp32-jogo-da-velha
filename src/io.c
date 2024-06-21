#include <Arduino.h>
#include "io.h"

// Função para definir a cor de um LED específico.
void set_led_color(int led_pos, Color color)
{
	int red_pin = reds[led_pos];
	int green_pin = greens[led_pos];

	switch (color) {
	case BLANK:
		digitalWrite(red_pin, LOW);
		digitalWrite(green_pin, LOW);
		break;
	case RED:
		digitalWrite(red_pin, HIGH);
		digitalWrite(green_pin, LOW);
		break;
	case GREEN:
		digitalWrite(red_pin, LOW);
		digitalWrite(green_pin, HIGH);
		break;
	}
}

// Função para imprimir o tabuleiro de LEDs.
void print_led_board(char board[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			Color c;
			switch (board[i][j]) {
			case ' ':
				c = BLANK;
				break;
			case 'X':
				c = GREEN;
				break;
			case 'O':
				c = RED;
				break;
			}
			set_led_color(i * SIZE + j, c);
		}
	}
}

// Função para detectar o estado do botão.
bool is_button_pressed(int button_pin)
{
	return digitalRead(button_pin) == HIGH;
}

// Função para mover o cursor para a próxima posição vazia.
void move_cursor(int *cursor_pos, char board[SIZE][SIZE])
{
	do {
		*cursor_pos = (*cursor_pos + 1) % (SIZE * SIZE);
	} while (board[*cursor_pos / SIZE][*cursor_pos % SIZE] != ' ');
}

// Função para piscar o LED na posição do cursor.
void flash_cursor(int cursor_pos, char player)
{
	Color color = (player == 'X') ? GREEN : RED;
	set_led_color(cursor_pos, color);
	delay(200);
	set_led_color(cursor_pos, BLANK);
}

void blink_winner(char player, char board[SIZE][SIZE])
{
	Color c = (player == 'X') ? GREEN : RED;

	for (int i = 0; i < 3; ++i) {
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				if (board[i][j] != player)
					continue;

				set_led_color(i * SIZE + j, BLANK);
				delay(100);
				set_led_color(i * SIZE + j, c);
				print_led_board(board);
			}
		}
		delay(500);
	}

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if (board[i][j] != player)
				set_led_color(i * SIZE + j, BLANK);
}

void blink_draw(char board[SIZE][SIZE])
{
	for (int i = 0; i < 5; ++i) {
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				set_led_color(i * SIZE + j, BLANK);
			}
		}
		delay(500);
		print_led_board(board);
		delay(500);
	}
}
