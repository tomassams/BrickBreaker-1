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

SDL_Rect Ball:: moveBall()
{
	vertical += horizontalVelocity;
	horizontal += verticalVelocity;
	ballRect = { horizontal, vertical, 13, 13 };
	return ballRect;
}

void Ball:: collision( SDL_Rect paddleRect, std::vector<Brick>* bricks )
{
	bool shouldChangeVerticalVelocity = false;
	bool shouldChangeHorizontalVelocity = false;

	std::thread handlePaddleCollision( [this, paddleRect, &shouldChangeHorizontalVelocity, &shouldChangeVerticalVelocity]()
	{
	   if ( paddleCollision(paddleRect) || vertical + ballScaling <= 50)
	   {
		   if (paddleCollisionAtEnd(paddleRect.x, paddleRect.w))
		   {
			   shouldChangeVerticalVelocity = true;
		   }
		   shouldChangeHorizontalVelocity = true;
	   }
	});

	std::thread handleBrickCollision( [this, &bricks, &shouldChangeHorizontalVelocity](){
		if ( ballBrickCollision(bricks) )
		{
			shouldChangeHorizontalVelocity = true;
		}
	});

	if (horizontal + ballScaling == WIDTH || horizontal + ballScaling == 0)
	{
		shouldChangeVerticalVelocity = true;
	}

	if (vertical + ballScaling >= HEIGHT)
	{
		outOfBounds = true;
	}
	handlePaddleCollision.join();
	handleBrickCollision.join();

	if ( shouldChangeVerticalVelocity )
	{
		changeVerticalVelocity();
	}
	if ( shouldChangeHorizontalVelocity )
	{
		changeHorizontalVelocity();
	}
}

/************************************ Paddle Collision *********************************************/
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

/************************************ Brick Collision *********************************************/
bool Ball:: ballBrickCollisionDetected( SDL_Rect brickRect )
{
	if (brickRect.x > ballRect.x + ballRect.w)
		return false;

	else if (brickRect.x + brickRect.w < ballRect.x)
		return false;

	else if (brickRect.y > ballRect.y + ballRect.h)
		return false;

	else return brickRect.y + brickRect.h >= ballRect.y;
}

bool Ball:: ballBrickCollision(std::vector<Brick>* bricks)
{
	bool changeVelocity = false;
	std::for_each(bricks->begin(), bricks->end(), [this, &changeVelocity] ( Brick &brick )
	{
		if (ballBrickCollisionDetected(brick.rect) && !brick.isHit())
		{
			brick.hit();
			changeVelocity = true;
			return;
		}
	});
	return changeVelocity;
}