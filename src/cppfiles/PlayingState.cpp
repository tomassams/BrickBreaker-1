//
// Created by ts on 4/24/2019.
//

#include <SDL.h>
#include "../header/PlayingState.h"


PlayingState::PlayingState() {
    paddle.setParams(800);
    paddle.setPaddlePositions(800, 600);

    paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };
    ballPosition = ball.moveBall(paddle.getPaddleY(), paddle.getPaddleX());

    renderer.initialize();
}

PlayingState::~PlayingState() {
    renderer.destroy();
}

void PlayingState::update() {

    paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };
    ballPosition = ball.moveBall(paddle.getPaddleY(), paddle.getPaddleX());

    // handleCollisions();
}

void PlayingState::display() {
    SDL_RenderClear(renderer.getRenderer());

    renderer.drawPaddle(paddlePosition);
    renderer.drawBall(ballPosition);
    // drawBricks()

    SDL_RenderPresent(renderer.getRenderer());
}

void PlayingState::handleEvent(const SDL_Event &event) {
    switch(inputManager.handle(event)) {
        case 0: return; // TODO: destroy / swap state with nextState()
        case 1: paddle.moveLeft();
            break;
        case 2: paddle.moveRight();
            break;
        default: return;
    }
}

std::unique_ptr<GameState> PlayingState::nextState() {
    // TODO: handle transition to next state (e.g. pause or exit/menu)
    return std::unique_ptr<GameState>();
}
