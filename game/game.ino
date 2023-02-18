#include "board.hpp"

bool working = true;
player winner;
board b;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(b.width * b.height, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel top = Adafruit_NeoPixel(b.width, 7, NEO_GRB + NEO_KHZ800);

void led(Adafruit_NeoPixel& strip, int r, int g, int b) {
  for (int i = 0; i < 42; i++ ) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  b.m_strip = &strip;
  b.m_strip->begin();
  b.top_strip = &top;
  b.top_strip->begin();
  led(*b.m_strip, 255, 0, 0);
  led(*b.top_strip, 255, 0, 0);
  delay(1000);
  led(*b.m_strip, 0, 255, 0);
  led(*b.top_strip, 0, 255, 0);
  delay(1000);
  led(*b.m_strip, 0, 0, 255);
  led(*b.top_strip, 0, 0, 255);
  delay(1000);
  led(*b.m_strip, 0, 0, 0);
  led(*b.top_strip, 0, 0, 0);
  b.top_strip->setPixelColor(3, 200, 40, 200);
  b.top_strip->show();
  b.update();
}

void loop() {
  if (working) {
    if (b.is_current_player_ai()) {
      int choice = b.choose_column();
      b.play(choice);
      b.update();
    } else {
      int left = digitalRead(2);
      int right = digitalRead(5);
      int check = digitalRead(3);
      if (left + right + check == 2) {
        if (check) {
          if (!left) {
            b.move_cursor(-1);
          } else {
            b.move_cursor(1);
          }
        } else {
          b.validate();
          b.update();
        }
        delay(400);
      }
    }
    winner = b.get_winner();
    if (winner != player::none) {
      b.win_anim();
      working = false;
    } else if (b.is_full()) {
      working = false;
    }
  }
}
