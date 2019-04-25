#include <algorithm>
#include "../header/Ball.h"

void Ball::initialize(int h, int w)
{
	width = w;
	height = h;
	setStartingPosition();
}

void Ball::setStartingPosition()
{
	outOfBounds = false;

	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_int_distribution<int> uniformDist(10, width - 10);

	vertical = height - 250;
	horizontal = uniformDist(engine);
	horizontalVelocity = 1;
	verticalVelocity = 1;

	if (horizontal > width / 2)
		changeVerticalVelocity();
}

SDL_Rect Ball:: moveBall()
{
	vertical += horizontalVelocity;
	horizontal += verticalVelocity;

	if (horizontal + ballScaling == width || horizontal  == 0)
	{
		changeVerticalVelocity();
	}

	if (getVerticalSize() >= height)
	{
		outOfBounds = true;
	}

	ballRect = { horizontal, vertical, 13, 13 };

	return ballRect;
}