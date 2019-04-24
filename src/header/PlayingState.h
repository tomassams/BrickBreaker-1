//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_PLAYINGSTATE_H
#define BRICKBREAKER_PLAYINGSTATE_H

#include <SDL.h>
#include <memory.h>
#include "GameState.h"
#include "InputManager.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Ball.h"

class PlayingState : public GameState {
public:
    PlayingState();
    ~PlayingState();
    void update() override;
    void display(Renderer &renderer) override;
    void handleEvent(const SDL_Event &event) override;
    std::unique_ptr<GameState> nextState() override;
private:
    InputManager inputManager;

    Paddle paddle;
    Ball ball;

    SDL_Rect paddlePosition;
    SDL_Rect ballPosition;
};


#endif //BRICKBREAKER_PLAYINGSTATE_H
