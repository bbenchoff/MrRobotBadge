//#include "RobotGFX.h"

#ifndef SNEK_H_
#define SNEK_H_

#include "Arduino.h"


class SnakeGame {
  private:
    uint8_t foodX; //(0-7)
    uint8_t foodY; //(0-15)
    uint16_t snakeLength;
    int8_t snakeHeadX;
    int8_t snakeHeadY;
    int8_t snakeHeadDX;
    int8_t snakeHeadDY;
    int8_t cur_x;
    int8_t cur_y;
    void placeFood();
    void gameOver();
    void changeDirection(int8_t dx, int8_t dy);  // should not run twice

  public:
    uint8_t snakeBoard[18][18];
    bool gameRunning;
    void init();
    void updateDirection(uint8_t u, uint8_t d, uint8_t l, uint8_t r);
    bool moveSnake();  // return true if move is valid
};
#endif SNEK_H_
