//
// Created by ts on 4/24/2019.
//

#include <SDL.h>
#include "../header/PlayingState.h"


PlayingState::PlayingState() {
    paddle.setParams(800);
    paddle.setPaddlePositions(800, 600);
    SDL_Rect r = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };

    renderer.initialize(r);
}

PlayingState::~PlayingState() {
    renderer.destroy();
}

void PlayingState::update() {
    // ball.update();
    // handleCollisions();
}

void PlayingState::display() {

    SDL_Rect p = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };
    SDL_Rect b = ball.moveBall(paddle.getPaddleY(), paddle.getPaddleX());

    SDL_RenderClear(renderer.getRenderer());
    renderer.drawPaddle(p);
    renderer.drawBall(b);
    SDL_RenderPresent(renderer.getRenderer());
    // drawBall()
    // drawBricks()
}

void PlayingState::handleEvent(const SDL_Event &event) {
    switch(inputManager.handle(event)) {
        case 0: return; // TODO: destroy / swap state
        case 1: paddle.moveLeft();
            break;
        case 2: paddle.moveRight();
            break;
        default: return;
    }
}

std::unique_ptr<GameState> PlayingState::nextState() {
    return std::unique_ptr<GameState>();
}
