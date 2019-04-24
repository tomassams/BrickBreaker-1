//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_GAMESTATE_H
#define BRICKBREAKER_GAMESTATE_H

#include <SDL.h>
#include <memory>
#include "Renderer.h"

class GameState {
public:
    //GameState();
    //~GameState();
    virtual void update() = 0;
    virtual void display(Renderer &renderer) = 0;
    virtual void handleEvent(const SDL_Event &event) = 0;
    virtual std::unique_ptr<GameState> nextState() = 0;
};

#endif //BRICKBREAKER_GAMESTATE_H
