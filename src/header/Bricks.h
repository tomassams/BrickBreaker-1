#ifndef BRICKBRAKER_BRICKS_H
#define BRICKBRAKER_BRICKS_H

#include <iostream>
#include <SDL.h>
#include "Brick.h"

class Bricks{
public:
	static const int brickY = 3, brickX = 7;
	int numberOfBricks = brickY*brickX;
	void InitializeBricks();
	bool ballBrickCollisionDetected(SDL_Rect brickRect, SDL_Rect ballRect);
	bool ballBrickCollision(SDL_Rect ballrect);
	Brick getBrick(int y, int x) {return brickArray[y][x];}

private:
	Brick brickArray[brickY][brickX];
};
#endif //BRICKBRAKER_BRICKS_H
