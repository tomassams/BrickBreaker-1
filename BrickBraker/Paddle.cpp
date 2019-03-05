//
//  Paddle.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 3/5/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include "Paddle.hpp"


void Paddle::setPaddlePositions(int w, int h)
{
	paddlex = (w / 2) - 40;
	paddley= h - 40;
}

void Paddle::moveLeft()
{
	if (getPaddleX() > 0) paddlex -= paddleSpeed;
}

void Paddle::moveRigth()
{
	if (getPaddleX() <= WIDTH - 90) paddlex += paddleSpeed;
}
