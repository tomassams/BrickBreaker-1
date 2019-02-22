//
//  Brick.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef Brick_hpp
#define Brick_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
class Brick{
public:
	SDL_Rect rect;
	bool isHit() {return onScreen;}
	void hit() {onScreen = true;}
	void createBrick(int y, int x) {rect = {y, x, brickW, brickH};}
	
private:
	bool onScreen = false;
	int brickW = 80, brickH = 35;
};

#endif /* Brick_hpp */
