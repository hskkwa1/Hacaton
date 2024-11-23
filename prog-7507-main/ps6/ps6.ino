#include "mastermind.h"
#include "lcd_wrapper.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void setup()
{
  lcd_init();
  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT);
  const int red[] = { LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4 };
  const int blue[] = { LED_BLUE_1, LED_BLUE_2, LED_BLUE_3, LED_BLUE_4 };
  for (int i = 0; i < 4; i++) {
    pinMode(red[i], OUTPUT);
    pinMode(blue[i], OUTPUT);
  }
  Serial.begin(9600);
  randomSeed(analogRead(A1));
}

void loop() 
{
  char* code = generate_code(false, 4);
  play_game(code);
  free(code);
}
