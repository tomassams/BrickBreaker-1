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
	if (y + ballScaling == WIDTH || y + ballScaling == 0)
	{
		changeVelocityY();
	}

	if ( paddleCollision(paddleY, paddleX) || x + ballScaling <= 0)
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

//TODO: Probably here paddle bug happens
bool Ball:: paddleCollision(int paddleY, int paddleX)
{
	return y + ballScaling >= paddleX
		&& y + ballScaling <= paddleX + 100
	 	&& x + ballScaling >= paddleY
	 	&& x + ballScaling <= paddleY + 40;
}