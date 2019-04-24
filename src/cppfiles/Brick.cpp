#include "../header/Brick.h"

void Brick:: resetBrick()
{
	isBrickHit = false;
}

bool Brick:: isHit()
{
	return isBrickHit;
}

void Brick:: hit()
{
	life--;
	if (life == 0) {
		isBrickHit = true;
	}
}