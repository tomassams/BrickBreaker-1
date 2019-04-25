#include "../header/Ball.h"

void Ball::setParams(int h, int w)
{
	HEIGHT = h;
	WIDTH = w;
	setBallStartPosition();
}

void Ball::setBallStartPosition()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(10, WIDTH-10);

	outOfBounds = false;
	vertical = HEIGHT-250;
	horizontal = dis(gen);
	horizontalVelocity = 1;
	verticalVelocity = 1;

	if (horizontal > WIDTH/2) changeVerticalVelocity();
}

SDL_Rect Ball:: moveBall( SDL_Rect paddleRect )
{
	std::thread handleCollision( [this, paddleRect]()
	{
		collision( paddleRect );
	});

	if (horizontal + ballScaling == WIDTH || horizontal + ballScaling == 0)
	{
		changeVerticalVelocity();
	}

	if (vertical + ballScaling >= HEIGHT)
	{
		outOfBounds = true;
	}

	handleCollision.join();
	vertical += horizontalVelocity;
	horizontal += verticalVelocity;

	return { horizontal, vertical, 13, 13 };
}

void Ball:: collision( SDL_Rect paddleRect )
{
	if ( paddleCollision(paddleRect) || vertical + ballScaling <= 50)
	{
		if (paddleCollisionAtEnd(paddleRect.x, paddleRect.w))
		{
			changeVerticalVelocity();
		}
		changeHorizontalVelocity();
	}
}

bool Ball:: paddleCollision( SDL_Rect paddleRect )
{
	return horizontal + ballScaling >= paddleRect.x
		&& horizontal + ballScaling <= paddleRect.x + paddleRect.w
	 	&& vertical + ballScaling >= paddleRect.y
	 	&& vertical + ballScaling <= paddleRect.y + paddleRect.h;
}

bool Ball:: paddleCollisionAtEnd( int x, int w )
{
	const bool onLeftSide = ( horizontal + ballScaling >= x
			&& horizontal + ballScaling <= (x + 20)
	);

	const bool onRightSide = (horizontal + ballScaling <= (x + w)
			&& horizontal + ballScaling >= (x + 60)
	);
	return (onLeftSide || onRightSide);
}