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
	std::thread handlePaddleCollision( [this, paddleRect]()
	{
	   if ( paddleCollision(paddleRect) || vertical + ballScaling <= 50)
	   {
		   if (paddleCollisionAtEnd(paddleRect.x, paddleRect.w))
		   {
			   changeVerticalVelocity();
		   }
		   changeHorizontalVelocity();
	   }
	});

	std::thread handleBrickCollision( [this, &bricks](){
		ballBrickCollision(bricks);
	});

	if (horizontal + ballScaling == WIDTH || horizontal + ballScaling == 0)
	{
		changeVerticalVelocity();
	}

	if (vertical + ballScaling >= HEIGHT)
	{
		outOfBounds = true;
	}
	handlePaddleCollision.join();
	handleBrickCollision.join();
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

void Ball:: ballBrickCollision(std::vector<Brick>* bricks)
{
	std::for_each(bricks->begin(), bricks->end(), [this](Brick &brick)
	{
		if (ballBrickCollisionDetected(brick.rect) && !brick.isHit())
		{
			brick.hit();
			changeHorizontalVelocity();
			return;
		}
	});
}