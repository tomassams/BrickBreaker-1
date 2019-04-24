//
// Created by ts on 4/24/2019.
//

#include "../header/MainMenuState.h"


MainMenuState::MainMenuState() {

}

MainMenuState::~MainMenuState() = default;

void MainMenuState::update() {

}

void MainMenuState::display(Renderer &renderer) {
    SDL_RenderClear(renderer.getRenderer());

    // do stuff
    // renderer.drawMainMenu();

    SDL_RenderPresent(renderer.getRenderer());
}

void MainMenuState::handleEvent() {

}

std::unique_ptr<GameState> MainMenuState::nextState() {
    return std::unique_ptr<GameState>();
}

bool MainMenuState::isActive() {
    return active;
}

