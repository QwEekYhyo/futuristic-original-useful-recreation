#include "board.hpp"

// char buf[80];
// int c;
bool working = true;
player winner;
board b;

void led(Adafruit_NeoPixel& strip, int r, int g, int b) {
   for(int i = 0; i < 42; i++ ) { // On fait une boucle pour définir la couleur de chaque led
      // setPixelColor(n° de led, Rouge, Vert, Bleu)
      strip.setPixelColor(i, r, g, b);       
   }
   strip.show(); // on affiche
}

// we do not need this anymore
int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
        switch (readch) {
            case '\r': // Ignore CR
                break;
            case '\n': // Return on new-line
                rpos = pos;
                pos = 0;  // Reset position index ready for next time
                return rpos;
            default:
                if (pos < len-1) {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    return 0;
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  b.m_strip = Adafruit_NeoPixel(b.width * b.height, 6, NEO_GRB + NEO_KHZ800);
  b.m_strip.begin();
  b.top_strip = Adafruit_NeoPixel(b.width, 7, NEO_GRB + NEO_KHZ800);
  b.top_strip.begin();
  led(b.m_strip, 255, 0, 0);
  led(b.top_strip, 255, 0, 0);
  delay(1000);
  led(b.m_strip, 0, 255, 0);
  led(b.top_strip, 0, 255, 0);
  delay(1000);
  led(b.m_strip, 0, 0, 255);
  led(b.top_strip, 0, 0, 255);
  delay(1000);
  led(b.m_strip, 0, 0, 0);
  led(b.top_strip, 0, 0, 0);
  b.top_strip.setPixelColor(3, 200, 40, 200);
  b.top_strip.show();
  Serial.begin(9600);
  b.update();
}

void loop() {  
  if (working) {
  int left = digitalRead(3);
  int right = digitalRead(5);
  int check = digitalRead(2);
  if (left + right + check == 2) {
  if (check) {
    if (!left) {
    b.move_cursor(0);
    } else {
    b.move_cursor(1);
    }
  } else {
    b.validate();
    b.update();
    winner = b.get_winner();
    if (winner != player::none) {
      String s_winner = winner == player::one ? "Player 1" : "Player 2";
      Serial.print(s_winner);
      Serial.println(" won !!");
      b.win_anim();
      working = false;
    } else if (b.is_full()) {
      Serial.println("Game over ! This is a tie");
      working = false;
    }
  }
  delay(400);
  }
  }
} 
