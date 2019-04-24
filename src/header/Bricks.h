#ifndef BRICKBREAKER_BRICKS_H
#define BRICKBREAKER_BRICKS_H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Brick.h"

class Bricks{
public:
	static const int brickY = 5, brickX = 9;
	int numberOfBricks = brickY*brickX;
	void InitializeBricks();
	static bool ballBrickCollisionDetected(SDL_Rect brickRect, SDL_Rect ballRect);
	bool ballBrickCollision(SDL_Rect ballRect);
	auto getBricks() { return brickVector;}
private:
	std::vector<Brick> brickVector;
};
#endif
