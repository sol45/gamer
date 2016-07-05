#include <Gamer.h>

Gamer gamer;

void setup() {
  gamer.begin();
};

struct Alien {
  int x;
  int y;
  boolean movingRight;
};

struct Blob {
  int x;
  int y;
  int width;
  int height;
};

struct Bullet {
  int x;
  int y;
};

Blob blob = {3, 6, 3, 2};
Bullet bullet = {blob.x+1, 5};

Alien alien = {0, 0, true};
boolean shot = false;

void drawBlob(int x, int y) {
  gamer.display[x][y] =1;
}

void drawAlien(int x, int y) {
  gamer.display[x][y] =1;
}
void animateAlien() {
  if(alien.x < 7 && alien.movingRight == true) { alien.x++;
  }
    else if (alien.x <= 7) { alien.movingRight = false, alien.x--;
    }
  if(alien.x == 0 && alien.movingRight== false) {alien.movingRight = true;
  }  
}

void drawRect() {
  for(int i = blob.x; i < (blob.x + blob.width); i++) {
    for(int j = blob.y; j < (blob.y + blob.height); j++)
    gamer.display[i][j] = 1;
    }

}
 

void blobControl() {
  if (gamer.isHeld(RIGHT) && blob.x != 5) {blob.x++;
  }
  if (gamer.isHeld(LEFT) && blob.x != 0) {blob.x--;
   }
  drawRect();
  delay(100);
}


//void shoot() {
// if (gamer.isPressed(UP)) {shot = true;
// }
//  while(shot == true) {
//    
//    gamer.display[blob.x + 1][y];
 //   y--;
 //   }
///    delay(100);
//    shot = !shot;


//}

void fire(int x, int y) {
  gamer.display[x][y] = 1;
}

void loop() {
  gamer.clear();
  drawRect();
  drawAlien(alien.x, alien.y);
  gamer.updateDisplay();
  delay(100);
  animateAlien();
  blobControl();
  fire(bullet.x, bullet.y);
 
}

