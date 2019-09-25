/*
  Скетч к проекту "Дневной Экскурсант"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverTripper/
  Исходники на GitHub: https://github.com/AlexGyver/GyverTripper/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver, AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

#define FREQ 10               // частота генератора отправки данных
#define KEY_PRESS KEY_D       // какая кнопка будет нажата
#define MODIFIER MOD_GUI_LEFT // модификатор (кнопка win (gui))

#define ATTEMPTS 3      // количество попыток распознать
#define DEADZONE 8000   // мёртвая зона
#define CLOSE_TIMEOUT 10000 // таймаут срабатывания
#define RADIO_PIN 0     // пин P0
 
#include "DigiKeyboard.h"

byte counter = 0;
uint32_t pulse = (long)1000000 / FREQ / 2;
uint32_t toutTimer;

void setup() {
  //Serial.begin(9600);
}

void loop() {
  long thisPulse = pulseIn(RADIO_PIN, HIGH, (long)pulse * 3);
  if (thisPulse < pulse + DEADZONE &&
      thisPulse > pulse - DEADZONE) {
    if (++counter >= ATTEMPTS) {
      //Serial.println("good!");
      if (millis() - toutTimer >= CLOSE_TIMEOUT) {
        toutTimer = millis();
        palundra();
      }
      counter = 0;
    }
  } else {
    //Serial.println("bad!");
    counter = 0;
  }
  //Serial.println(pulseIn(2, HIGH, (long)pulse * 3));
}

void palundra() {
  DigiKeyboard.sendKeyPress(KEY_PRESS, MODIFIER);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyPress(0);
}
