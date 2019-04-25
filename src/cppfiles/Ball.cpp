#include "../header/Ball.h"

void Ball::setBallStartPosition()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(10, WIDTH);

	outOfBounds = false;
	vertical = HEIGHT-250;
	horizontal = dis(gen);
	velocityX = 1;
	velocityY = 1;

	if (horizontal > WIDTH/2) changeHorizontalVelocity();
}

SDL_Rect Ball:: moveBall(const SDL_Rect paddleRect)
{
	if (horizontal + ballScaling == WIDTH || horizontal + ballScaling == 0)
	{
		changeHorizontalVelocity();
	}

	collision(paddleRect);

	if (vertical + ballScaling >= HEIGHT)
	{
		outOfBounds = true;
	}

	vertical += velocityX;
	horizontal += velocityY;

	return { horizontal, vertical, 13, 13 };
}

void Ball:: collision(const SDL_Rect paddleRect)
{
	if ( paddleCollision(paddleRect)
		 || vertical + ballScaling <= 0
		 || vertical + ballScaling >= HEIGHT) //DEVMODE
	{
		changeVerticalVelocity();

		if (paddleCollisionAtEnd(paddleRect.x, paddleRect.y, paddleRect.h))
		{
			changeHorizontalVelocity();
		}
	}
}

bool Ball:: paddleCollision(const SDL_Rect paddleRect)
{
	return horizontal + ballScaling >= paddleRect.x
		&& horizontal + ballScaling <= paddleRect.x + paddleRect.w
	 	&& hitPaddleSurface(paddleRect.y, paddleRect.h);
}

bool Ball:: paddleCollisionAtEnd(const int x, const int y, const int h)
{
	const bool onLeftSide = ( horizontal + ballScaling >= y && horizontal + ballScaling <= y + 20);
	const bool onRightSide = (horizontal + ballScaling <= y + 80 && horizontal + ballScaling > y + 60);
	return (onLeftSide || onRightSide) &&  hitPaddleSurface(x, h);

}

bool Ball:: hitPaddleSurface(const int x, const int h)
{
	return (vertical + ballScaling >= x
		   && vertical + ballScaling <= x + h
	);
}