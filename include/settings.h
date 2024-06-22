#pragma once // Garante que esse arquivo não será incluído mais de uma vez.

#ifdef __cplusplus
extern "C" {
#endif

#include "player.h"

typedef struct {
	int game_mode;
	Difficulty difficulty;
	Difficulty difficulty2;
	enum { PLAYER, CPU } first;
} Options;

typedef enum {
	DEFAULT_SETTINGS,
	SERIAL_SETTINGS,
	BLUETOOTH_SETTINGS
} SettingsMode;

typedef enum {
	// Tela de seleção de modo de jogo.
	PVP = 1,
	PVE = 2,

	// Tela de seleção de dificuldade.
	EASY_DIFF = 3,
	NORMAL_DIFF = 4,
	HARD_DIFF = 5,

	// Tela de escolha de quem vai jogar primeiro.
	PLAYER_FIRST = 6,
	CPU_FIRST = 7,

	// Tela de jogo.
	SCORE_P1 = 8,
	SCORE_P2 = 9,
} BtMsg;

void set_sm(void);
void modal_setup(void);
void get_settings(Options *opt);

#ifdef __cplusplus
}
#endif
