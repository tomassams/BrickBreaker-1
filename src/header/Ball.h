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
	void setParams(int h, int w);
	SDL_Rect moveBall();
	void changeHorizontalVelocity() { horizontalVelocity = -horizontalVelocity; }
	void changeVerticalVelocity() { verticalVelocity = -verticalVelocity; }
	bool isOutOfBounds() const { return outOfBounds; }
	void setBallStartPosition();
	void collision( SDL_Rect paddleRect, std::vector<Brick>* bricks );

private:
	SDL_Rect ballRect;
	int HEIGHT, WIDTH;
	int vertical, horizontal;
	int horizontalVelocity, verticalVelocity;
	int ballScaling = 13;
	bool outOfBounds = false;
	bool ballBrickCollisionDetected( SDL_Rect brickRect );
	void ballBrickCollision(std::vector<Brick>* bricks);
	bool paddleCollision( SDL_Rect paddleRect );
	bool paddleCollisionAtEnd( int x, int w );
};
#endif
