#ifndef BRICKBRAKER_BRICK_H
#define BRICKBRAKER_BRICK_H
#include <iostream>
#include <SDL.h>
class Brick{

public:
	SDL_Rect rect;
	bool isHit() {return isBrickHit;}
	void hit() {isBrickHit = true;}
	void createBrick(int y, int x) {
		isBrickHit = false;
		rect = {y, x, brickW, brickH};
	}

private:
	bool isBrickHit = false;
	int brickW = 80, brickH = 35;
};

#endif