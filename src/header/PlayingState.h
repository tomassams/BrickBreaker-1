#ifndef BRICKBREAKER_PLAYINGSTATE_H
#define BRICKBREAKER_PLAYINGSTATE_H

#include <SDL.h>
#include <memory.h>
#include <thread>
#include <algorithm>

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
	int health = 3;
	bool active = true;

    InputManager inputManager;
    std::shared_ptr<Renderer> renderer;

    Bricks bricks;
    Paddle paddle;
    Ball ball;

    SDL_Rect paddlePosition;
    SDL_Rect ballPosition;

	bool isActive(); // temp
    std::vector<SDL_Rect> brickPositions[Bricks::brickX * Bricks::brickY];
};
#endif
