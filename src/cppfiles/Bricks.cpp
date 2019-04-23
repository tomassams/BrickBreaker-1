#include "../header/Bricks.h"

void Bricks:: InitializeBricks()
{
	brickVector->clear();

	int y = 50, x = 20;
	for (int i = 0; i < brickY; i++)
	{
		for (int j = 0; j < brickX; j++)
		{
			brickVector->push_back(Brick(y, x));
			y += 100;
		}
		y = 50;
		x += 50;
	}
}

bool Bricks:: ballBrickCollisionDetected(SDL_Rect brickRect, SDL_Rect ballRect)
{
	if (brickRect.x > ballRect.x + ballRect.w)
		return false;

	else if (brickRect.x + brickRect.w < ballRect.x)
		return false;

	else if (brickRect.y > ballRect.y + ballRect.h)
		return false;

	else return brickRect.y + brickRect.h >= ballRect.y;
}

bool Bricks:: ballBrickCollision(SDL_Rect ballRect)
{
	bool returnBool = false;

	std::for_each(brickVector->begin(), brickVector->end(), [ballRect, &returnBool](Brick &brick) {
		if (ballBrickCollisionDetected(brick.rect, ballRect) && !brick.isHit())
		{
			brick.hit();
			returnBool = true;
		}
	});

	return returnBool;
}

Brick Bricks::getBrick(int y, int x)
{
	if (y == 0) return brickVector-> at(x);

	int position = (x == 0) ? brickX * y : x + brickX * y;
	return brickVector-> at(position);
}
