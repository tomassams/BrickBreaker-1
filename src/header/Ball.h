#ifndef BRICKBREAKER_BALL_H
#define BRICKBREAKER_BALL_H

#include <iostream>
#include <random>
#include <SDL.h>

class Ball{
public:
	void setParams(int h, int w)
	{
		HEIGHT = h;
		WIDTH = w;
		setBallStartPosition();
	}

	SDL_Rect moveBall(SDL_Rect paddleRect);
	void changeVerticalVelocity() {velocityX = -velocityX;}
	void changeHorizontalVelocity() {velocityY = -velocityY;}
	bool isOutOfBounds() const {return outOfBounds;}
	void setBallStartPosition();

private:
	int HEIGHT, WIDTH;
	int vertical, horizontal, velocityX, velocityY;
	int ballScaling = 13;
	bool outOfBounds = false;
	bool paddleCollision(SDL_Rect paddleRect);
	bool paddleCollisionAtEnd(int x, int w);
	void collision(SDL_Rect paddleRect);
};

#endif
