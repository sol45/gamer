#include <Gamer.h>

Gamer gamer;

void setup() {
  gamer.begin();
  Serial.begin(9600);
  makeAliens();
  
};


struct Alien{
  int x;
  int y;
  boolean movingRight;
  boolean beenShot;
  boolean dead;
  
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
const int aliensPerRow = 4;
int gameSpeed = 80; //lower is faster
int score = 0;
int counter = 0;
Blob blob = {3, 7, 3, 1};
Bullet bullet = {5, 7, false};
const int rows = 4;
const int cols = 4;
struct Alien aliens[rows][cols];
boolean alienRight = true;
boolean gameOver = false;
boolean newLine = false;

//void drawBlob(int x, int y) {
//  gamer.display[x][y] =1;
//}

//void drawAlien(int x, int y) {
  //if(alien.beenShot == false) {
 // gamer.display[x][y] =1;
 //}
//}
void resetBullet(int x, int y) {
  gamer.display[x][y] = 1;
}


//void animateAlien() {
//  if(alien.x < 3 && alien.movingRight == true) { alien.x++;
 // }
 //   else if (alien.x <= 3) { alien.movingRight = false, alien.x--;
//    }
//  if(alien.x == 0 && alien.movingRight== false) {alien.movingRight = true;
//  }  
//}

void drawBlob() {
  for(int i = blob.x; i < (blob.x + blob.width); i++) {
    for(int j = blob.y; j < (blob.y + blob.height); j++)
     gamer.display[i][j] = 1;
    }

}


void makeAliens() {
   int offSet = 0;
   int x = 0;
   int y = 0;
   for(int i = 0; i < rows; i++) {
        for(int j = 0; j < (cols - offSet); j++) {
       
          aliens[i][j]= {x + offSet, y, true, false, false};   
         
           x = x + 2;
        }
        x=0;
       y++;
        if(offSet == 1) {
          offSet = 0;
        }
         else {
            offSet = 1;
       }
    }
}
void drawAliens() {
  for(int i= 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      int x = aliens[i][j].x;
      int y = aliens[i][j].y; 
      //Serial.println("y" + y);
      if(aliens[i][j].dead == false) {
       gamer.display[x][y] = 1;
      }
    }
  }
}


void moveAliens() {
  for(int i = 0; i < rows; i++) { 
     for(int j = 0; j < cols; j++) {
       if(alienRight == true) {  
       aliens[i][j].x = aliens[i][j].x + (-2 * aliensPerRow + 9);
       }
         else {
        aliens[i][j].x = aliens[i][j].x - (-2 * aliensPerRow + 9);
         }
       if(counter == gameSpeed) {
      //Serial.print("NEWLINE");
      aliens[i][j].y++;
      }
    }
  }
    if(counter == gameSpeed) {
    counter = 0;   
    }
   
   alienRight = !alienRight;
   counter++;
}

   
void blobControl() {
  if (gamer.isHeld(RIGHT) && blob.x != 5) {blob.x++;
  }
  if (gamer.isHeld(LEFT) && blob.x != 0) {blob.x--;
   }
  drawBlob();
  delay(100);
}


void shoot() {
    if(gamer.isPressed(UP)) { bullet.shot = true;
    }
    if(bullet.y <= 7 && bullet.shot == true) { bullet.y-- ;
  }    
    if(bullet.y == -1) {bullet.shot = false; 
     bullet.y = 7;
     }
    if(bullet.shot == false) {bullet.x = blob.x + 1;
   
    }

}


void detectImpact() {
  for(int i = 0; i < aliensPerRow; i++) {
    for(int j = 0; j < cols; j++) {
      if(aliens[i][j].x == bullet.x && aliens[i][j].y == bullet.y && aliens[i][j].dead == false) {
       bullet.shot = false;
        bullet.y = 7;
       aliens[i][j].dead = true;
        score = score + 1;
       resetBullet(blob.x + 1, bullet.y);
        }
     } 
  }
}

void checkGame() {
 for(int i = 0; i < aliensPerRow; i++) {
  for(int j = 0; j < cols; j++) {
    if(aliens[i][j].y >= 7 && aliens[i][j].dead == false) {
      gameOver = true;
    
    
    }
   }
  }
  //if(gamer.isPressed(START)) {started = true;
  }

void reset() {
  counter = 0;
  newLine = false;
  alienRight = true;
  score = 0;
  gameSpeed = 60;
  makeAliens();
  gameOver = false;
}

boolean nextLevel() {
  boolean allDead = true;
  for(int i = 0; i < aliensPerRow; i++) {
    for(int j = 0; j < cols; j++) {
      if(aliens[i][j].dead  == false) {
        allDead = false; 
        
      }
       
      }
  
    }
    return allDead;
  }

void loop() {
  if(gameOver == false) {
      checkGame();
    //if(started == true) {
      gamer.clear();
      drawBlob();
      moveAliens();
      drawAliens();
      resetBullet(bullet.x, bullet.y);
      gamer.updateDisplay();
      delay(100);
      detectImpact();
      blobControl();
      shoot();
    
    if(nextLevel() == true) {
      if(gameSpeed != 15) {
        gameSpeed = gameSpeed - 15;
        }
        counter = 0;
        gameOver = false;
        newLine = false;
        alienRight = true;
        makeAliens();
      
      
    }
   
  }
    else {
     //if(gameOver == true) {
      gamer.clear();
      gamer.showScore(score); 
      gamer.updateDisplay();
      delay(2000);
      reset();  
  }
  

 
}

