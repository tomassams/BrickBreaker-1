#ifndef BRICKBRAKER_BRICK_H
#define BRICKBRAKER_BRICK_H
#include <iostream>
#include <SDL.h>
class Brick {

public:
	Brick(){
		isBrickHit = false;
	};

	Brick(int y, int x) {
		isBrickHit = false;
		rect = {y, x, brickW, brickH};
	};
	SDL_Rect rect{};

	void resetBrick() { isBrickHit = false; }
	bool isHit() { return isBrickHit; }
	void hit() { isBrickHit = true; }

private:
	bool isBrickHit = false;
	int brickW = 80, brickH = 35;
};
#endif