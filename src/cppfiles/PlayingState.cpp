#include <SDL.h>
#include "../header/PlayingState.h"

PlayingState::PlayingState(Renderer &r) {
    renderer = r;

    paddle = Paddle();
    ball = Ball();
    bricks = Bricks();

    renderer.initializeGame();

    SDL_Log("playingState constructed");
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

    SDL_Log("playingstate update");

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

void PlayingState::display(Renderer &rr) {
    SDL_Log("playingstate display1");
    SDL_RenderClear(renderer.getRenderer());
    SDL_Log("playingstate display1");

    // TODO: loop through a SDL_
    renderer.drawBricks(bricks); // causes crash
    SDL_Log("playingstate display--1");
    renderer.drawPaddle(paddlePosition);
    SDL_Log("playingstate display--2");
    renderer.drawBall(ballPosition);
    SDL_Log("playingstate display--3");

    SDL_RenderPresent(renderer.getRenderer());
    SDL_Log("playingstate display2");
}

void PlayingState::handleEvent() {
    SDL_Log("playingstate eventhandle");
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
    SDL_Log("playingstate nextstate return");
    // TODO: handle transition to next state (e.g. pause or exit/menu)
    return nullptr;
}