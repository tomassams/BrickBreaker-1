#include "../header/Ball.h"

void Ball::settParam(int h, int w)
{
	HIGHT = h;
	WIDTH = w;
}

void Ball::reset()
{
	outOfBounds = false;
	x = 200;
	y = 200;
	velx = 1;
	vely = 1;
}

SDL_Rect Ball::moveBall(int paddley, int paddlex)
{
	if (y+ballscaling == WIDTH || y+ballscaling == 0)
		changeVelocityY();

	if ((y + ballscaling >= paddlex
		 && y + ballscaling <= paddlex+100
		 && x + ballscaling >= paddley
		 && x + ballscaling <= paddley+40)
		//|| x + ballscaling == HIGHT //TODO:- DEVMODE SHOULD BE REMOVED
		|| x + ballscaling <= 0)
	{ changeVelocityX(); }

	if (x + ballscaling >= HIGHT) outOfBounds = true;

	x += velx;
	y += vely;

	return {y, x, 40, 40};
}