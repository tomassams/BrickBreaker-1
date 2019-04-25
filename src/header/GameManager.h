#ifndef BRICKBREAKER_GAMEMANAGER_H
#define BRICKBREAKER_GAMEMANAGER_H

#include <iostream>
#include <SDL.h>
#include <memory>
#include <thread>

#include "InputManager.h"
#include "Ball.h"
#include "Bricks.h"
#include "Paddle.h"
#include "Renderer.h"
#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"

class GameManager{
public:
	void init();
	void play();
	void quit();
	bool gameEnded = false;
private:
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(Renderer());
};

#endif
