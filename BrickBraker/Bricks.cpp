//
//  Bricks.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include "Bricks.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "Brick.hpp"

void Bricks:: InitilizeBricks()
{
	int z = 50, s = 20;
	for (int i = 0; i < brickY; i++)
	{
		for (int j = 0; j < brickX; j++)
		{
			brickArray[i][j].createBrick(z, s);
			z += 100;
		}
		
		z = 50;
		s += 50;
	}
}

bool Bricks:: ballBrickCollisionDetected(SDL_Rect brickRect, SDL_Rect ballrect)
{
	if (brickRect.x > ballrect.x + ballrect.w)
		return false;
	
	else if (brickRect.x + brickRect.w < ballrect.x)
		return false;
	
	else if (brickRect.y > ballrect.y + ballrect.h)
		return false;
	
	else if (brickRect.y+brickRect.h < ballrect.y)
		return false;
	
	else
		return true;
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
