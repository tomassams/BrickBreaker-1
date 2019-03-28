#ifndef BRICKBRAKER_PADDLE_H
#define BRICKBRAKER_PADDLE_H

#include <iostream>
#include <SDL.h>

class Paddle
{

public:
	void setParams(int w) {WIDTH = w;}
	SDL_Rect paddleRect() {return {paddleX, paddleY, 80, 20}; }
	void setPaddlePositions(int w, int h);
	int getPaddleX() {return paddleX;}
	int getPaddleY() {return paddleY;}
	void moveLeft();
	void moveRight();

private:
	int WIDTH;
	int paddleX = 0, paddleY = 0;
	int paddleSpeed = 2;
};

#endif
