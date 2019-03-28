#ifndef BRICKBRAKER_PADDLE_H
#define BRICKBRAKER_PADDLE_H

#include <iostream>
#include <SDL.h>

class Paddle
{

public:
	SDL_Rect paddleRect() {return {paddlex, paddley, 80, 20}; }
	void setParams(int w) {WIDTH = w;}
	void setPaddlePositions(int w, int h);
	int getPaddleX() {return paddlex;}
	int getPaddleY() {return paddley;}
	void moveLeft();
	void moveRight();

private:
	int WIDTH;
	int paddlex = 0, paddley = 0;
	int paddleSpeed = 2;
};

#endif
