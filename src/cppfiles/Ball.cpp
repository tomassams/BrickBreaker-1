#include <algorithm>
#include "../header/Ball.h"

void Ball::setParams(int h, int w)
{
	HEIGHT = h;
	WIDTH = w;
	setBallStartPosition();
}

void Ball::setBallStartPosition()
{
	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_int_distribution<int> uniformDist(10, WIDTH-10);

	outOfBounds = false;
	vertical = HEIGHT-250;
	horizontal = uniformDist(engine);
	horizontalVelocity = 1;
	verticalVelocity = 1;

	if (horizontal > WIDTH/2) changeVerticalVelocity();
}

SDL_Rect Ball:: moveBall()
{
	vertical += horizontalVelocity;
	horizontal += verticalVelocity;

	if (horizontal + ballScaling == WIDTH || horizontal  == 0)
	{
		changeVerticalVelocity();
	}

	if (getVerticalSize() >= HEIGHT)
	{
		outOfBounds = true;
	}

	ballRect = { horizontal, vertical, 13, 13 };
	return ballRect;
}