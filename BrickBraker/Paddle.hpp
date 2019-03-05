//
//  Paddle.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Paddle
{

public:
	SDL_Rect paddleRect() {return {paddlex, paddley, 80, 20}; }
	void setParams(int w) {WIDTH = w;}
	void setPaddlePositions(int w, int h);
	int getPaddleX() {return paddlex;}
	int getPaddleY() {return paddley;}
	void moveLeft();
	void moveRigth();
	
private:
	int WIDTH;
	int paddlex = 0, paddley = 0;
	int paddleSpeed = 2;
};
#endif /* Paddle_hpp */
