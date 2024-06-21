#include <Arduino.h>

#define BTN1 35
#define BTN2 34
#define NUM_LEDS 9
static const int reds[NUM_LEDS] = { 15, 0, 16, 5, 19, 22, 13, 14, 26 };
static const int greens[NUM_LEDS] = { 2, 4, 17, 18, 33, 23, 12, 27, 25 };

static void boot_blink();

void setup()
{
	Serial.begin(115200);
	for (int i = 0; i < NUM_LEDS; ++i) {
		pinMode(greens[i], OUTPUT);
		pinMode(reds[i], OUTPUT);
	}

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
}
