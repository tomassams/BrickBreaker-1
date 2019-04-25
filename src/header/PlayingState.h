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
#include "CollisionManager.h"

class PlayingState : public GameState
{
public:
    explicit PlayingState(std::shared_ptr<Renderer> renderer);
    ~PlayingState();
    void update() override;
    void display() override;
    void handleEvent() override;
    std::unique_ptr<GameState> nextState() override;
private:
	int health = 5;
	bool active = true;

	bool isActive() { return active; };
	bool exitToMenu = false;

	Status status;

	CollisionManager collisionManager;
    InputManager inputManager;
    std::shared_ptr<Renderer> renderer;

    Bricks bricks = Bricks();
    Paddle paddle = Paddle();
    Ball ball = Ball();

    SDL_Rect paddlePosition{};
    SDL_Rect ballPosition{};

	std::vector<SDL_Rect> brickPositions[Bricks::brickColumns * Bricks::brickRows];
};
#endif
