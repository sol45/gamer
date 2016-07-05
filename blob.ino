#include <Gamer.h>

Gamer gamer;
void setup() {
  gamer.begin();

};


struct Blob {
  int x;
  int y;
};

Blob blob = {4, 4};


void loop() {
wibble(blob.x, blob.y);
if (gamer.isHeld(RIGHT)) {
  blob.x++;
}
if (gamer.isHeld(LEFT)) {
  blob.x--;
}
if (gamer.isHeld(UP)) {
  blob.y--;
}
if (gamer.isHeld(DOWN)) {
 blob.y++;
}

}
void wibble(int x, int y) {
  gamer.clear();
  gamer.display[x][y] =1;
  gamer.updateDisplay();
  delay(150);
}

