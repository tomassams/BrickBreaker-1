#include "../header/Ball.h"

void Ball::reset()
{
	outOfBounds = false;
	vertical = 200;
	horizontal = 200;
	velocityX = 1;
	velocityY = 1;
}

SDL_Rect Ball:: moveBall(int paddlePositionX, int paddlePositionY)
{
	if (horizontal + ballScaling == WIDTH || horizontal + ballScaling == 0)
		changeVelocityY();

	if ( paddleCollision(paddlePositionX, paddlePositionY)
		|| vertical + ballScaling <= 0
		|| vertical + ballScaling >= HEIGHT) //DEVMODE
		changeVelocityX();

	if (vertical + ballScaling >= HEIGHT)
		outOfBounds = true;

	vertical += velocityX;
	horizontal += velocityY;

	return {horizontal, vertical, 15, 15};
}

bool Ball:: paddleCollision(int paddlePositionX, int paddlePositionY)
{
	return horizontal + ballScaling >= paddlePositionY
		&& horizontal + ballScaling <= paddlePositionY + 90 //TODO: Tweak value to remove paddle bug
	 	&& vertical + ballScaling >= paddlePositionX;
	 	//&& vertical + ballScaling <= paddlePositionX - 20; //TODO: Tweak value to remove paddle bug
}