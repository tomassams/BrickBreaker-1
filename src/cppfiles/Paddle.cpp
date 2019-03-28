#include "../header/Paddle.h"

void Paddle::setPaddlePositions(int w, int h)
{
	paddlex = (w / 2) - 40;
	paddley= h - 40;
}

void Paddle::moveLeft()
{
	if (getPaddleX() > 0) paddlex -= paddleSpeed;
}

void Paddle::moveRight()
{
	if (getPaddleX() <= WIDTH - 90) paddlex += paddleSpeed;
}
