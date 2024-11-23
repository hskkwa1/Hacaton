#include "mastermind.h"
#include "lcd_wrapper.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

LiquidCrystal_I2C lcd2(0x27, 16, 2);

long randNumber;

char* generate_code(bool repeat, int length);
void turn_off_leds();
void get_score(char* secret, char* guess, int* peg_a, int* peg_b);
void render_leds(const int peg_a, const int peg_b);
char incrementDigit(char digit);

void play_game(char* secret) {

  if (strlen(secret) == NULL) {
    return NULL;
  }

  char guess[3];
  int peg_a = 0;
  int peg_b = 0;  

  lcd2.init();
  lcd2.backlight();

  lcd_print_at(0, 0, "Hello there!");
  lcd_print_at(0, 1, "Let's play game!");

  delay(5000);

  for (int lives = 1; lives <= 10; lives++) {
    lcd_clear();
    lcd2.backlight();

    lcd_print_at(0, 0, "What secret is?:");
    lcd_print_at(0, 1, "Attemp:");

    bool enterPressed = false;
    char digits[] = { '0', '0', '0', '0' };

    lcd2.setCursor(11, 1);
    lcd2.print(digits[0]);
    lcd2.setCursor(12, 1);
    lcd2.print(digits[1]);
    lcd2.setCursor(13, 1);
    lcd2.print(digits[2]);
    lcd2.setCursor(14, 1);
    lcd2.print(digits[3]);

    while (!enterPressed) {
      if (digitalRead(BTN_1_PIN) == HIGH) {
        delay(300);
        digits[0] = incrementDigit(digits[0]);
        lcd2.setCursor(11, 1);
        lcd2.print(digits[0]);
      }
      if (digitalRead(BTN_2_PIN) == HIGH) {
        delay(300);
        digits[1] = incrementDigit(digits[1]);
        lcd2.setCursor(12, 1);
        lcd2.print(digits[1]);
      }
      if (digitalRead(BTN_3_PIN) == HIGH) {
        delay(300);
        digits[2] = incrementDigit(digits[2]);
        lcd2.setCursor(13, 1);
        lcd2.print(digits[2]);
      }
      if (digitalRead(BTN_4_PIN) == HIGH) {
        delay(300);
        digits[3] = incrementDigit(digits[3]);
        lcd2.setCursor(14, 1);
        lcd2.print(digits[3]);
      }

      enterPressed = (digitalRead(BTN_ENTER_PIN) == HIGH);
    }

    guess[0] = digits[0];
    guess[1] = digits[1];
    guess[2] = digits[2];
    guess[3] = digits[3];
    get_score(secret, guess, &peg_a, &peg_b);
    render_leds(peg_a, peg_b);

    delay(5000);
    turn_off_leds();

    if (peg_a == 4) {
      lcd_clear();
      lcd_print_at(0, 0, "Victory!");
      lcd_print_at(0, 1, "Well done!");
      delay(7000);
      lcd_clear();
      break;
    }

    if (peg_a != 4 && lives == 10 ) {
      lcd_clear();
      lcd_print_at(0, 0, "You lose!");
      lcd_print_at(0, 1, "Secret was:");
      lcd2.setCursor(11, 1);
      lcd2.print(secret);
      delay(7000);
      lcd_clear();
      break;
    }
  }
}

char incrementDigit(char digit) {
  if (digit == '9') {
    return '0';
  } else {
    return digit + 1;
  }
}


char* generate_code(bool repeat, int length) {
  if (length < 1) {
    return NULL;
  }

  if (!repeat && length > 10) {
    return NULL;
  }

  char* code = (char*)malloc((length + 1) * sizeof(char));
  code[length] = '\0';

  int i;
  for (i = 0; i < length; i++) {
    int digit;

    if (repeat) {
      digit = random(10);
    } else {
      bool unique = false;
      while (!unique) {
        digit = random(10);
        unique = true;

        for (int j = 0; j < i; j++) {
          if (code[j] == digit + '0') {
            unique = false;
            break;
          }
        }
      }
    }

    code[i] = digit + '0';
  }

  return code;
}



void turn_off_leds() {
  digitalWrite(LED_RED_1, 0);
  digitalWrite(LED_RED_2, 0);
  digitalWrite(LED_RED_3, 0);
  digitalWrite(LED_RED_4, 0);
  digitalWrite(LED_BLUE_1, 0);
  digitalWrite(LED_BLUE_2, 0);
  digitalWrite(LED_BLUE_3, 0);
  digitalWrite(LED_BLUE_4, 0);
}



void get_score(char* secret, char* guess, int* peg_a, int* peg_b) {
    *peg_a = 0;
    *peg_b = 0;

    int secret_count[10] = {0};  
    int guess_count[10] = {0};

    for (int i = 0; secret[i] != '\0' && guess[i] != '\0'; i++) {
        if (secret[i] == guess[i]) {
            (*peg_a)++;
        } else {
            secret_count[secret[i] - '0']++;
            guess_count[guess[i] - '0']++;
        }
    }

    for (int i = 0; secret[i] != '\0'; i++) {
        if (secret[i] != guess[i]) {
            int digit = secret[i] - '0';
            if (secret_count[digit] > 0 && guess_count[digit] > 0) {
                (*peg_b)++;
                secret_count[digit]--; 
                guess_count[digit]--;  
            }
        }
    }
}
