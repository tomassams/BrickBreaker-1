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

class Paddle{
public:
	SDL_Rect paddleRect() {return {paddlex, paddley, 80, 20}; }
	void setPaddlePositions(int w, int h) {paddlex = (w/2)-40; paddley= h-40;}
	int getPaddleX() {return paddlex;}
	int getPaddleY() {return paddley;}
	void moveLeft() {paddlex -= 20;}
	void moveRigth() {paddlex += 20;}
	
private:
	int paddlex = 0, paddley= 0;
	
};
#endif /* Paddle_hpp */
