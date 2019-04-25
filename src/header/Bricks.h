#ifndef BRICKBREAKER_BRICKS_H
#define BRICKBREAKER_BRICKS_H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Brick.h"

class Bricks{
public:
	static const int brickY = 5, brickX = 9;
	void InitializeBricks(int top);
	std::vector<Brick>* getBricks() { return &brickVector;}
private:
	std::vector<Brick> brickVector;
};
#endif
