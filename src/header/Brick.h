#ifndef BRICKBREAKER_BRICK_H
#define BRICKBREAKER_BRICK_H

#include <iostream>
#include <SDL.h>

class Brick {

public:
	Brick();
	Brick(int verticalSpacing, int horizontalSpacing, int life);

	SDL_Rect rect{};
	void hit();
	bool isHit() { return isBrickHit; }
	int getHealth() { return currentHealth;}
	void resetBrick();

private:
	bool isBrickHit = false;
	int brickWidth = 80, brickHeight = 34;
	int currentHealth;
	int maxHealth;
};
#endif