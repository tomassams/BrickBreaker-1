#ifndef BRICKBRAKER_BALL_H
#define BRICKBRAKER_BALL_H

#include <iostream>
#include <SDL.h>

class Ball{
public:
	void settParam(int h, int w);

	SDL_Rect moveBall(int paddleY, int paddleX);
	void changeVelocityX() {velx = -velx;}
	void changeVelocityY() {vely = -vely;}
	bool isOutOfBounds() const {return outOfBounds;}
	void reset();

private:
	int x = 200, y = 200, velx = 1, vely = 1;
	int ballscaling = 20;
	int HIGHT, WIDTH;
	bool outOfBounds = false;
};

#endif //BRICKBRAKER_BALL_H
