#ifndef BRICKBREAKER_PLAYINGSTATE_H
#define BRICKBREAKER_PLAYINGSTATE_H

#include <SDL.h>
#include <memory.h>
#include <thread>
#include <vector>
#include <algorithm>

#include "MainMenuState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Ball.h"
#include "Bricks.h"
#include "Brick.h"

class PlayingState : public GameState
{
public:
    PlayingState(std::shared_ptr<Renderer> renderer);
    ~PlayingState();
    void update() override;
    void display() override;
    void handleEvent() override;
    std::unique_ptr<GameState> nextState() override;
private:
	int numBrokenBricks = 0;
	int health = 5;
	bool active = true;

    InputManager inputManager;
    std::shared_ptr<Renderer> renderer;

    Bricks bricks;
    Paddle paddle;
    Ball ball;

    SDL_Rect paddlePosition;
    SDL_Rect ballPosition;

	bool isActive();
    std::vector<SDL_Rect> brickPositions[Bricks::brickX * Bricks::brickY];

    bool paused = false;
    bool exitToMenu = false;
};
#endif
