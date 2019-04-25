#ifndef BRICKBREAKER_BALL_H
#define BRICKBREAKER_BALL_H

#include <iostream>
#include <random>
#include <thread>
#include <SDL.h>

class Ball{
public:
	void setParams(int h, int w);
	SDL_Rect moveBall(SDL_Rect paddleRect);
	void changeHorizontalVelocity() { horizontalVelocity = -horizontalVelocity; }
	void changeVerticalVelocity() { verticalVelocity = -verticalVelocity; }
	bool isOutOfBounds() const { return outOfBounds; }
	void setBallStartPosition();

private:
	int HEIGHT, WIDTH;
	int vertical, horizontal;
	int horizontalVelocity, verticalVelocity;
	int ballScaling = 13;
	bool outOfBounds = false;
	bool paddleCollision(SDL_Rect paddleRect);
	bool paddleCollisionAtEnd(int x, int w);
	void collision(SDL_Rect paddleRect);
};
#endif
