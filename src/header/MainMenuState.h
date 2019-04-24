//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_MAINMENUSTATE_H
#define BRICKBREAKER_MAINMENUSTATE_H


#include "GameState.h"
#include "InputManager.h"

class MainMenuState : public GameState {
public:
    MainMenuState();
    ~MainMenuState();
    void update() override;
    void display(Renderer &renderer) override;
    void handleEvent() override;
    std::unique_ptr<GameState> nextState() override;
    bool isActive() override;
private:
    InputManager inputManager;
    bool active = true;
};


#endif //BRICKBREAKER_MAINMENUSTATE_H
