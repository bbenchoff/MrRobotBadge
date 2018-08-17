#include "snek.h"

void SnakeGame::init() {
  for (uint8_t y=0;y<18;y++) {
    for (uint8_t x=0;x<18;x++) {
      snakeBoard[y][x]=0;
    }
  }
  snakeLength=3;
  cur_x = 1;
  cur_y = 0;
  snakeHeadX=random(4)+2;
  snakeHeadY=random(12)+2;
  uint8_t moveDirection=random(4);
  switch (moveDirection) {
    case 0:  // up
      snakeHeadDX=0;  snakeHeadDY=-1; break;
    case 1:  // down
      snakeHeadDX=0;  snakeHeadDY=1;  break;
    case 2:  // left
      snakeHeadDX=-1; snakeHeadDY=0;  break;
    case 3:  // right
      snakeHeadDX=1;  snakeHeadDY=0;
  }
  // Draw the snake of length=3
  snakeBoard[snakeHeadY][snakeHeadX]=3;
  snakeBoard[snakeHeadY-snakeHeadDY][snakeHeadX-snakeHeadDX]=2;
  snakeBoard[snakeHeadY-snakeHeadDY*2][snakeHeadX-snakeHeadDX*2]=1;
  placeFood();
  gameRunning=true;
}

void SnakeGame::gameOver() {
  gameRunning=false;
}

void SnakeGame::placeFood() {
  foodX = random(14)+2;
  foodY = random(14)+2;
  while(snakeBoard[foodY][foodX]!=0) {
    foodX = random(14)+2;
    foodY = random(14)+2;
  }
  snakeBoard[foodY][foodX]=snakeLength+1;
}

bool SnakeGame::moveSnake() {
  snakeHeadX = ((snakeHeadX+snakeHeadDX)%18);
  snakeHeadY = ((snakeHeadY+snakeHeadDY)%18);
  if( snakeHeadX < 0 ){
    snakeHeadX = 18;
  }
  if( snakeHeadY < 0 ){
    snakeHeadY = 18;
  }

  uint8_t temp = snakeBoard[snakeHeadY][snakeHeadX];
  // if the new snakeHead is already occupied by part of the snake body, then return false, game over
  if (temp>1 && temp<=snakeLength){
    gameRunning = false;
    return false;
  }
  if (snakeHeadX == foodX && snakeHeadY == foodY) {
    snakeLength+=1;
    placeFood();
  }
  else {
    for (uint8_t y=0; y<18; y++) {
      for (uint8_t x=0; x<18; x++) {
        if (snakeBoard[y][x]>0 && snakeBoard[y][x]<=snakeLength) snakeBoard[y][x]-=1;
      }
    }
    snakeBoard[snakeHeadY][snakeHeadX]=snakeLength;
  }
  return true;
}

void SnakeGame::changeDirection(int8_t dx, int8_t dy) {
  snakeHeadDX=dx;
  snakeHeadDY=dy;
}

void SnakeGame::updateDirection(uint8_t u, uint8_t d, uint8_t l, uint8_t r)
{
//  // Snake can only go up / down / left / right
//  // snake can't go the opposite way
  if( (u > 0 || d > 0) && cur_y == 0 ){
    cur_x = 0;
    if( u ){
      cur_y = -1;
    }else{
      cur_y = 1;
    }
  }
  else if( (r > 0 || l > 0 ) and cur_x== 0) {
    cur_y = 0;
    if( l ){
      cur_x = -1;
    }else{
      cur_x = 1;
    }
  }
  changeDirection(cur_x,cur_y);
}
