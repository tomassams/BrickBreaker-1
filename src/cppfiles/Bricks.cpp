#include "../header/Bricks.h"

void Bricks:: InitializeBricks()
{
	brickVector.clear();

	int horizontalSpacing = 10;

	for (int i = 0; i < brickY; i++)
	{
		int verticalSpacing = 10;
		for (int j = 0; j < brickX; j++)
		{
			brickVector.emplace_back(verticalSpacing, horizontalSpacing, brickY-i);
			verticalSpacing += 88;
		}
		horizontalSpacing += 40;
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
	std::for_each(brickVector.begin(), brickVector.end(), [ballRect, &returnBool](Brick &brick)
	{
		if (ballBrickCollisionDetected(brick.rect, ballRect) && !brick.isHit())
		{
			brick.hit();
			returnBool = true;
		}
	});
	return returnBool;
}
