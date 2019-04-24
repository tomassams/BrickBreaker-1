#ifndef BRICKBRAKER_GAMEMANAGER_H
#define BRICKBRAKER_GAMEMANAGER_H

#include <iostream>
#include <SDL.h>

#include "Ball.h"
#include "Bricks.h"
#include "InputManager.h"
#include "Paddle.h"
#include "Renderer.h"

class GameManager{

public:
	void init();
	void play();
	void quit();
	bool gameEnded = false;
private:
    Renderer stateRenderer;
};

#endif
