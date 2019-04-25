#include "../header/Paddle.h"

void Paddle::setPaddlePositions(int w, int h)
{
	paddleX = (w / 2) - 40;
	paddleY= h - 40;
}

void Paddle::moveLeft()
{
	if (getPaddleX() > 0)
		paddleX -= paddleSpeed;
}

void Paddle::moveRight()
{
	if (getPaddleX() <= WIDTH - 90)
		paddleX += paddleSpeed;
}
