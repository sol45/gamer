#include <Gamer.h>

Gamer gamer;

void setup() {
  gamer.begin();
};

struct Alien {
  int x;
  int y;
  boolean movingRight;
  boolean beenShot;
  
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
  boolean shot;
};

int score = 0;
Blob blob = {3, 6, 3, 2};
Bullet bullet = {5, 6, false};
Alien alien = {0, 0, true, false};


//void drawBlob(int x, int y) {
//  gamer.display[x][y] =1;
//}

void drawAlien(int x, int y) {
  if(alien.beenShot == false) {gamer.display[x][y] =1;
}
}
void resetBullet(int x, int y) {
  gamer.display[x][y] = 1;
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


void shoot() {
    if(gamer.isPressed(UP)) { bullet.shot = true;
    }
    if(bullet.y <= 6 && bullet.shot == true) { bullet.y-- ;
  }    
    if(bullet.y == -1) {bullet.shot = false; bullet.y = 6;
    }
    if(bullet.shot == false) {bullet.x = blob.x + 1;
    }

}

void detectImpact() {
  if(bullet.x == alien.x && bullet.y == alien.y) {
    score + 10;
    resetBullet(bullet.x, bullet.y);
    alien.beenShot = true;
    
    }
}

void loop() {
  gamer.clear();
  drawRect();
  drawAlien(alien.x, alien.y);
  resetBullet(bullet.x, bullet.y);
  gamer.updateDisplay();
  delay(100);
  animateAlien();
  blobControl();
  shoot();
  detectImpact();
 
}

