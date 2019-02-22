//
//  Ball.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include <iostream>
#include "Ball.hpp"
#include <SDL2/SDL.h>


SDL_Rect Ball::moveBall(int HIGHT, int WIDTH, int paddley, int paddlex)
{
	if (y == WIDTH-20 ||y == -20)
		changeVelocityY();
	
	int ballscaling = 20;
	
	if ((y + ballscaling >= paddlex && y + ballscaling <= paddlex+100 && x + ballscaling >= paddley && x + ballscaling <= paddley+40)
		||(x == HIGHT-20 ||x == -20)){
		changeVelocityX();
		if ((rand() % 2) +1 == 1) changeVelocityY();
	}

	
	x += velx;
	y += vely;
	return {y, x, 40, 40};
}




