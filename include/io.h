#pragma once // Garante que esse arquivo não será incluído mais de uma vez.

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"

#define BTN1 35
#define BTN2 34
#define NUM_LEDS 9

static const int reds[NUM_LEDS] = { 15, 0, 16, 5, 19, 22, 13, 14, 26 };
static const int greens[NUM_LEDS] = { 2, 4, 17, 18, 33, 23, 12, 27, 25 };

typedef enum {
	BLANK,
	RED,
	GREEN
} Color;

void print_led_board(char board[SIZE][SIZE]);
void set_led_color(int led_pos, Color color);
bool is_button_pressed(int button_pin);
void move_cursor(int *cursor_pos, char board[SIZE][SIZE]);
void flash_cursor(int cursor_pos, char player);
void boot_blink(void);
void blink_winner(char player, char board[SIZE][SIZE]);
void blink_draw(char board[SIZE][SIZE]);
void blink_all(Color c);

#ifdef __cplusplus
}
#endif
