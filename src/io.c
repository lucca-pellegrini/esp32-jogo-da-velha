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
