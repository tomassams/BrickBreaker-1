#include "../header/Brick.h"

Brick:: Brick()
{
	SDL_Log("Brick empty constructor called");
	isBrickHit = false;
	currentHealth = 1;
	maxHealth = 1;
}

Brick:: Brick( int verticalSpacing, int horizontalSpacing, int life )
{
	SDL_Log("Brick NOT empty constructor called");
	currentHealth = life;
	maxHealth = life;
	isBrickHit = false;
	rect = { verticalSpacing, horizontalSpacing, brickWidth, brickHeight };
}

void Brick:: hit()
{
	currentHealth--;
	if (currentHealth == 0)
	{
		isBrickHit = true;
	}
}

void Brick:: resetBrick()
{
	currentHealth = maxHealth;
	isBrickHit = false;
}