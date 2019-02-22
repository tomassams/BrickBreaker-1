//
//  Bricks.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef Bricks_hpp
#define Bricks_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Brick.hpp"

class Bricks{
public:
	static const int brickY = 3, brickX = 7;
	int numberOfBricks = brickY*brickX;
	void InitilizeBricks();
	bool ballBrickCollisionDetected(SDL_Rect brickRect, SDL_Rect ballrect);
	bool ballBrickCollision(SDL_Rect ballrect);
	Brick getBrick(int y, int x) {return brickArray[y][x];}
	
	
private:
	Brick brickArray[brickY][brickX];
};

#endif /* Bricks_hpp */
