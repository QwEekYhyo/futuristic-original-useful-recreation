#include "board.hpp"

char buf[80];
int c;
bool working = true;
player winner;
board b;

void led(Adafruit_NeoPixel& strip, int r, int g, int b) {
   for(int i = 0; i < 42; i++ ) { // On fait une boucle pour définir la couleur de chaque led
      // setPixelColor(n° de led, Rouge, Vert, Bleu)
      strip.setPixelColor(i, r, g, b);       
   }
   strip.show(); // on affiche
   delay(1000);
}

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
  b.m_strip = Adafruit_NeoPixel(b.width * b.height, 6, NEO_GRB + NEO_KHZ800);
  b.m_strip.begin();
  led(b.m_strip, 255, 0, 0);
  led(b.m_strip, 0, 255, 0);
  led(b.m_strip, 0, 0, 255);
  led(b.m_strip, 0, 0, 0);
  Serial.begin(9600);
  b.update();
}

void loop() {  
  if (working) {
  Serial.println("Which column do you wish to play in ?");
  while (readline(Serial.read(), buf, 80) == 0) {}
  c = atoi(buf);
  if (c != 2) {
    b.move_cursor(c);
    Serial.println(c);
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
  }
} 
