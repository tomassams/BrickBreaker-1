#ifndef BRICKBRAKER_BRICK_H
#define BRICKBRAKER_BRICK_H
#include <iostream>
#include <SDL.h>
class Brick {

public:
	Brick(){
		isBrickHit = false;
		life = 1;
	};

	Brick(int verticalSpacing, int horizontalSpacing, int life) {
		this->life = life;
		isBrickHit = false;
		rect = { verticalSpacing, horizontalSpacing, brickWidth, brickHeight };
	};

	SDL_Rect rect{};
	void resetBrick();
	bool isHit();
	void hit();

private:
	bool isBrickHit = false;
	int brickWidth = 80, brickHeight = 35;
	int life;
};
#endif