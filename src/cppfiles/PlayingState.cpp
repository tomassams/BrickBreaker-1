#include <utility>

#include <utility>

#include <SDL.h>
#include "../header/PlayingState.h"
#include "../header/MainMenuState.h"

PlayingState::PlayingState(std::shared_ptr<Renderer> r) {
    exitToMenu = false;
    renderer = std::move(r);

    paddle = Paddle();
    ball = Ball();
    bricks = Bricks();

    renderer->initializeGame();

    paddle.setParams(800);
    paddle.setPaddlePositions(800, 600);
    ball.setParams(600, 800);

    bricks.InitializeBricks();

    paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 20 };
    ballPosition = ball.moveBall(paddle.getPaddleY(), paddle.getPaddleX());
}

PlayingState::~PlayingState() {
};

void PlayingState::update() {
    if(paused) {
        return;
    }

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

void PlayingState::display() {
    if(paused) {
        return;
    }

    SDL_RenderClear(renderer->getRenderer());

    renderer->drawBricks(bricks);
    renderer->drawPaddle(paddlePosition);
    renderer->drawBall(ballPosition);

    SDL_RenderPresent(renderer->getRenderer());
}

void PlayingState::handleEvent() {
    switch(inputManager.handle()) {
        case QUIT_GAME:
            exitToMenu = !exitToMenu;
            break;
        case MOVE_LEFT:
            paddle.moveLeft();
            break;
        case MOVE_RIGHT:
            paddle.moveRight();
            break;
        case TOGGLE_PAUSE:
            paused = !paused;
        default:
            return;
    }
}

bool PlayingState::isActive() {
    return active;
}

std::unique_ptr<GameState> PlayingState::nextState() {

    if(exitToMenu) {
        std::unique_ptr<GameState> nextState(new MainMenuState(renderer));
        renderer->destroyGame();

        return nextState;
    }

    return nullptr;
}