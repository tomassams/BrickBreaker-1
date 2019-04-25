#ifndef BRICKBREAKER_BALL_H
#define BRICKBREAKER_BALL_H

#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <SDL.h>
#include "Brick.h"

class Ball{
public:
	SDL_Rect moveBall();
	SDL_Rect getCurrentPosition() const {return ballRect;}

	void setParams(int h, int w);
	void changeHorizontalVelocity() { horizontalVelocity = -horizontalVelocity; }
	void changeVerticalVelocity() { verticalVelocity = -verticalVelocity; }
	bool isOutOfBounds() const { return outOfBounds; }
	void setBallStartPosition();

	int getVerticalSize() const { return vertical + ballScaling; }
	int getHorizontalSize() const { return horizontal + ballScaling; }

private:
	SDL_Rect ballRect;
	int HEIGHT, WIDTH;
	int vertical, horizontal;
	int horizontalVelocity, verticalVelocity;
	int ballScaling = 13;
	bool outOfBounds = false;
};
#endif
