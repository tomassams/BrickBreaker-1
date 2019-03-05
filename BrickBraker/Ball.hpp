//
//  Ball.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Ball{
public:
	void settParam(int h, int w);
	
	SDL_Rect moveBall(int paddley, int paddlex);
	void changeVelocityX() {velx = -velx;}
	void changeVelocityY() {vely = -vely;}
	bool isOutOfBounds() const {return outOfBounds;}
	void reset();
	
private:
	int x = 200, y = 200, velx = 1, vely = 1;
	int ballscaling = 20;
	int HIGHT, WIDTH;
	bool outOfBounds = false;
};

#endif /* Ball_hpp */
