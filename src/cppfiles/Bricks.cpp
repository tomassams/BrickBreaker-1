//
// Created by Henrik Anthony Odden Sandberg on 2019-03-28.
//

#include "../header/Bricks.h"

void Bricks:: InitilizeBricks()
{
	int z = 50, s = 20;
	for (auto &i : brickArray) {
		for (auto &j : i) {
			j.createBrick(z, s);
			z += 100;
		}

		z = 50;
		s += 50;
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

bool Bricks:: ballBrickCollision(SDL_Rect ballrect)
{
	for(int i = 0; i < brickY; i++)
		for (int j= 0; j < brickX; j++)
		{
			if (ballBrickCollisionDetected(brickArray[i][j].rect, ballrect) && !brickArray[i][j].isHit())
			{
				brickArray[i][j].hit();
				return true;
			}
		}
	return false;
}