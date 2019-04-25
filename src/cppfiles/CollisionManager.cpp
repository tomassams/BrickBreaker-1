#include "CollisionManager.h"

void CollisionManager:: collision(Ball* ball, SDL_Rect paddleRect, std::vector<Brick>* bricks )
{
	bool shouldChangeVerticalVelocity = false;
	bool shouldChangeHorizontalVelocity = false;

	std::thread handlePaddleCollision( [this, paddleRect, &ball, &shouldChangeHorizontalVelocity, &shouldChangeVerticalVelocity]()
	{
	   if ( paddleCollision(ball->getHorizontalSize(), ball->getVerticalSize(), paddleRect) || ball->getVerticalSize() <= 50)
	   {
		   if (paddleCollisionAtEnd(ball->getHorizontalSize(), paddleRect.x, paddleRect.w))
		   {
			   shouldChangeVerticalVelocity = true;
		   }
		   shouldChangeHorizontalVelocity = true;
	   }
	});

	std::thread handleBrickCollision( [this, ball, &bricks, &shouldChangeHorizontalVelocity](){
		if ( ballBrickCollision(ball->getCurrentPosition(), bricks) )
		{
			shouldChangeHorizontalVelocity = true;
		}
	});

	handlePaddleCollision.join();
	handleBrickCollision.join();

	if ( shouldChangeVerticalVelocity )
	{
		ball->changeVerticalVelocity();
	}
	if ( shouldChangeHorizontalVelocity )
	{
		ball->changeHorizontalVelocity();
	}
}

/************************************ Paddle Collision *********************************************/
bool CollisionManager:: paddleCollision( int horizontal, int vertical, SDL_Rect paddleRect)
{
	return horizontal >= paddleRect.x
		   && horizontal <= paddleRect.x + paddleRect.w
		   && vertical  >= paddleRect.y
		   && vertical  <= paddleRect.y + paddleRect.h;
}

bool CollisionManager:: paddleCollisionAtEnd(int horizontal, int x, int w )
{
	const bool onLeftSide = ( horizontal >= x && horizontal <= (x + 20) );
	const bool onRightSide = (horizontal <= (x + w) && horizontal >= (x + 60) );
	return (onLeftSide || onRightSide);
}

/************************************ Brick Collision *********************************************/
bool CollisionManager:: ballBrickCollisionDetected( SDL_Rect ballRect, SDL_Rect brickRect)
{
	if (brickRect.x > ballRect.x + ballRect.w)
		return false;

	else if (brickRect.x + brickRect.w < ballRect.x)
		return false;

	else if (brickRect.y > ballRect.y + ballRect.h)
		return false;

	else return brickRect.y + brickRect.h >= ballRect.y;
}

bool CollisionManager:: ballBrickCollision( SDL_Rect ballRect, std::vector<Brick>* bricks)
{
	bool changeVelocity = false;
	std::for_each(bricks->begin(), bricks->end(), [this, ballRect, &changeVelocity] ( Brick &brick )
	{
		if (ballBrickCollisionDetected(ballRect, brick.rect) && !brick.isHit())
		{
			brick.hit();
			brickCollisionCounter++;
			changeVelocity = true;
			return;
		}
	});
	return changeVelocity;
}