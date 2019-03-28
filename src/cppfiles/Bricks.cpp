//
// Created by Henrik Anthony Odden Sandberg on 2019-03-28.
//

#include "../header/Bricks.h"

void Bricks:: InitializeBricks()
{
	int y = 50, x = 20;
	for (auto &i : brickArray) {
		for (auto &j : i) {
			j.createBrick(y, x);
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

bool Bricks:: ballBrickCollision(SDL_Rect ballrect)
{
	for (auto &i : brickArray)
		for (auto &j : i) {
			if (ballBrickCollisionDetected(j.rect, ballrect) && !j.isHit())
			{
				j.hit();
				return true;
			}
		}
	return false;
}