#include "../header/Ball.h"

void Ball::reset()
{
	outOfBounds = false;
	x = 200;
	y = 200;
	velocityX = 1;
	velocityY = 1;
}

SDL_Rect Ball:: moveBall(int paddlePositionX, int paddlePositionY)
{
	if (y + ballScaling == WIDTH || y + ballScaling == 0)
		changeVelocityY();

	if ( paddleCollision(paddlePositionX, paddlePositionY) || x + ballScaling <= 0)
		changeVelocityX();

	if (x + ballScaling >= HEIGHT)
		outOfBounds = true;

	x += velocityX;
	y += velocityY;

	return {y, x, 15, 15};
}

bool Ball:: paddleCollision(int paddlePositionX, int paddlePositionY)
{
	return y + ballScaling >= paddlePositionY
		&& y + ballScaling <= paddlePositionY + 80 //TODO: Tweak value to remove paddle bug
	 	&& x + ballScaling >= paddlePositionX
	 	&& x + ballScaling <= paddlePositionX + 20; //TODO: Tweak value to remove paddle bug
}