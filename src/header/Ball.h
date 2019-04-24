#ifndef BRICKBRAKER_BALL_H
#define BRICKBRAKER_BALL_H

#include <iostream>
#include <SDL.h>

class Ball{
public:
	void setParams(int h, int w)
	{
		HEIGHT = h;
		WIDTH = w;
	}

	SDL_Rect moveBall(int paddlePositionX, int paddlePositionY);
	void changeVelocityX() {velocityX = -velocityX;}
	void changeVelocityY() {velocityY = -velocityY;}
	bool isOutOfBounds() const {return outOfBounds;}
	void reset();

private:
	int vertical = 300, horizontal = 200, velocityX = 1, velocityY = 1;
	int ballScaling = 5;
	int HEIGHT, WIDTH;
	bool outOfBounds = false;
	bool paddleCollision(int paddlePositionX, int paddlePositionY);
};

#endif
