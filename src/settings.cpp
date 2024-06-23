#include "HardwareSerial.h"
#include <Arduino.h>
#include <BluetoothSerial.h>

#include "settings.h"
#include "io.h"

static SettingsMode SM;
static Options SettingsBT = { .is_set = false };
static BluetoothSerial SerialBT;

void set_sm(void)
{
	if (is_button_pressed(BTN1)) {
		SM = BLUETOOTH_SETTINGS;
		blink_all(GREEN);
	} else if (is_button_pressed(BTN2)) {
		SM = SERIAL_SETTINGS;
		blink_all(RED);
	} else {
		SM = DEFAULT_SETTINGS;
	}
}

void modal_setup(void)
{
	switch (SM) {
	case SERIAL_SETTINGS:
		Serial.begin(115200);
		break;
	case BLUETOOTH_SETTINGS:
		SerialBT.begin("O Jogo da Velha");
		Serial.begin(115200);
		break;
	default:
		break;
	}
}

static void get_serial_settings(Options *opt)
{
	// Pede ao usuário que escolha um modo de jogo.
	do {
		Serial.println("Escolha um modo de jogo:");
		Serial.println("1. Jogador vs jogador");
		Serial.println("2. Jogador vs computador");
		Serial.println("3. Computador vs computador");
		while (Serial.available() == 0) {
		} // Espera o usuário digitar.
		opt->game_mode = Serial.parseInt();
	} while (opt->game_mode < 1 || opt->game_mode > 3);

	// Caso escolha jogar contra o computador, decida quem jogará primeiro.
	if (opt->game_mode == 2) {
		int primeiro = -1;
		do {
			Serial.println("\nQuem jogará primeiro?");
			Serial.println("1. Jogador");
			Serial.println("2. Computador");
			while (Serial.available() == 0) {
			} // Espera o usuário digitar.
			primeiro = Serial.parseInt();
		} while (primeiro < 1 || primeiro > 2);
	}

	// Leia a dificuldade do computador.
	if (opt->game_mode == 2 || opt->game_mode == 3) {
		do {
			Serial.println("\nEscolha a dificuldade:");
			Serial.println("1. Fácil");
			Serial.println("2. Normal");
			Serial.println("3. Difícil");
			while (Serial.available() == 0) {
			} // Espera o usuário digitar.
			opt->difficulty =
				static_cast<Difficulty>(Serial.parseInt());
		} while (opt->difficulty < EASY || opt->difficulty > HARD);
	}

	// Caso escolha assistir, leia a dificuldade do oponente.
	if (opt->game_mode == 3) {
		do {
			Serial.println(
				"\nEscolha a dificuldade para o oponente:");
			Serial.println("1. Fácil");
			Serial.println("2. Normal");
			Serial.println("3. Difícil");
			while (Serial.available() == 0) {
			} // Espera o usuário digitar.
			opt->difficulty2 =
				static_cast<Difficulty>(Serial.parseInt());
		} while (opt->difficulty2 < EASY || opt->difficulty2 > HARD);
	}
}

BtAction check_and_handle_bt(void)
{
	if (!SerialBT.available())
		return CONTINUE;

	SettingsBT.is_set = false;
	return RETURN;
}

static void get_bt_settings(Options *opt)
{
	if (SettingsBT.is_set) {
		*opt = SettingsBT;
		return;
	}

	while (!SettingsBT.is_set) {
		while (!SerialBT.available())
			blink_loading(GREEN);

		int msg = SerialBT.read();
		Serial.print("Código recebido por Bluetooth: ");

		switch (msg) {
		case PVP:
			Serial.println("PVP");
			opt->game_mode = 1;
			opt->first = Options::CPU;
			opt->is_set = SettingsBT.is_set = true;
			break;
			break;
		case PVE:
			Serial.println("PVE");
			opt->game_mode = 2;
			break;

		case EASY_DIFF:
			Serial.println("EASY_DIFF");
			opt->difficulty = EASY;
			break;
		case NORMAL_DIFF:
			Serial.println("NORMAL_DIFF");
			opt->difficulty = NORMAL;
			break;
		case HARD_DIFF:
			Serial.println("HARD_DIFF");
			opt->difficulty = HARD;
			break;

		case PLAYER_FIRST:
			Serial.println("PLAYER_FIRST");
			opt->first = Options::PLAYER;
			opt->is_set = SettingsBT.is_set = true;
			break;
		case CPU_FIRST:
			Serial.println("CPU_FIRST");
			opt->first = Options::CPU;
			opt->is_set = SettingsBT.is_set = true;
			break;
		}
	}

	SettingsBT = *opt;
}

void get_settings(Options *opt)
{
	switch (SM) {
	case SERIAL_SETTINGS:
		get_serial_settings(opt);
		return;
	case BLUETOOTH_SETTINGS:
		get_bt_settings(opt);
		return;
	default:
		return;
	}
}
