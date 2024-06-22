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

typedef enum { EASY_DIFF, NORMAL_DIFF, HARD_DIFF } BtMsg;

void set_sm(void);
void modal_setup(void);
void get_settings(Options *opt);

#ifdef __cplusplus
}
#endif
