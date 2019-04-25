//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_MAINMENUSTATE_H
#define BRICKBREAKER_MAINMENUSTATE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include "GameState.h"
#include "InputManager.h"

class MainMenuState : public GameState {
public:
    MainMenuState(std::shared_ptr<Renderer> r);
    void update() override;
    void display() override;
    void handleEvent() override;
    std::unique_ptr<GameState> nextState() override;
    bool isActive() { return active; };
private:
    InputManager inputManager;
    int selectedItem = -1;
    int highlightedPosition = 0;
    bool active = true;
    std::shared_ptr<Renderer> renderer = nullptr;
};

#endif //BRICKBREAKER_MAINMENUSTATE_H
