#ifndef BRICKBREAKER_PLAYINGSTATE_H
#define BRICKBREAKER_PLAYINGSTATE_H

#include <SDL.h>
#include <memory.h>
#include "GameState.h"
#include "InputManager.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Ball.h"
#include "Bricks.h"
#include "Brick.h"

class PlayingState : public GameState {
public:
    PlayingState(Renderer &renderer);
    ~PlayingState();
    void update() override;
    void display(Renderer &renderer) override;
    void handleEvent() override;
    std::unique_ptr<GameState> nextState() override;
private:
    InputManager inputManager;
    Renderer renderer;

    Bricks bricks;
    Paddle paddle;
    Ball ball;

    SDL_Rect paddlePosition;
    SDL_Rect ballPosition;

    int numBrokenBricks = 0;

    std::vector<SDL_Rect> brickPositions[Bricks::brickX * Bricks::brickY];

    bool active = true; // temp
    bool isActive(); // temp
};


#endif //BRICKBREAKER_PLAYINGSTATE_H
