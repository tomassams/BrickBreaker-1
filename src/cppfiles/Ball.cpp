#include "../header/Ball.h"


void Ball::reset()
{
	outOfBounds = false;
	x = 200;
	y = 200;
	velocityX = 1;
	velocityY = 1;
}

SDL_Rect Ball::moveBall(int paddleY, int paddleX)
{
	if (y+ballScaling == WIDTH || y+ballScaling == 0)
	{
		changeVelocityY();
	}


	if ((y + ballScaling >= paddleX
		 && y + ballScaling <= paddleX+100
		 && x + ballScaling >= paddleY
		 && x + ballScaling <= paddleY+40)
		//|| x + ballScaling == HEIGHT //DEVMODE
		|| x + ballScaling <= 0)
	{
		changeVelocityX();
	}

	if (x + ballScaling >= HEIGHT)
	{
		outOfBounds = true;
	}

	x += velocityX;
	y += velocityY;

	return {y, x, 40, 40};
}