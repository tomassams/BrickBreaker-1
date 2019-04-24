#include <SDL.h>
#include "../header/PlayingState.h"

PlayingState::PlayingState() {
    paddle.setParams(800);
    paddle.setPaddlePositions(800, 600);
    ball.setParams(600, 800);

    bricks.InitializeBricks();

    paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };
    ballPosition = ball.moveBall(paddle.getPaddleY(), paddle.getPaddleX());

    //mBall.reset(); // from old activateGame(), not sure if necessary
}
PlayingState::~PlayingState() = default;

void PlayingState::update() {

    paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };
    ballPosition = ball.moveBall(paddle.getPaddleY(), paddle.getPaddleX());

//    if (ball.isOutOfBounds()) { active = false; }

    if (bricks.ballBrickCollision(ballPosition))
    {
        numBrokenBricks++;
        ball.changeVelocityX();

        //if (numBrokenBricks == bricks.numberOfBricks){ active = false;} //TODO: Finish state is now grater than just the number of bricks
    }

}

void PlayingState::display(Renderer &renderer) {
    SDL_RenderClear(renderer.getRenderer());

    // TODO: loop through a SDL_
    renderer.drawBricks(bricks);
    renderer.drawPaddle(paddlePosition);
    renderer.drawBall(ballPosition);

    SDL_RenderPresent(renderer.getRenderer());
}

void PlayingState::handleEvent() {
    switch(inputManager.handle()) {
        case 0:
            active = false;
            break;
        case 1:
            paddle.moveLeft();
            break;
        case 2:
            paddle.moveRight();
            break;
        default:
            return;
    }
}

// temp
bool PlayingState::isActive() {
    return active;
}

std::unique_ptr<GameState> PlayingState::nextState() {
    // TODO: handle transition to next state (e.g. pause or exit/menu)
    return std::unique_ptr<GameState>();
}