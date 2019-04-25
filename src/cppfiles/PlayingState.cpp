#include <SDL.h>
#include "../header/PlayingState.h"
#include "../header/MainMenuState.h"

PlayingState::PlayingState(std::shared_ptr<Renderer> r) {

    renderer = r;

    paddle = Paddle();
    ball = Ball();
    bricks = Bricks();

    renderer->initializeGame();

    int topOfGameScreen = 800/100*6;
    paddle.setParams(800);
    paddle.setPaddlePositions(800, 600);
    ball.setParams(600, 800);
    bricks.InitializeBricks(topOfGameScreen);

	update();

	//mBall.reset(); // from old activateGame(), not sure if necessary
}
PlayingState::~PlayingState() = default;

void PlayingState:: update() {

    paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 26 };
    ballPosition = ball.moveBall(paddlePosition);

    if (ball.isOutOfBounds()) {
		if (--health == 0)
		{
			active = false;
			display();
		} else
		{
			ball.setBallStartPosition();
		}
	}

	if (bricks.ballBrickCollision(ballPosition))
	{
		numBrokenBricks++;
		ball.changeVerticalVelocity();

		//if (numBrokenBricks == bricks.numberOfBricks){ active = false;}
		// TODO: Finish state is now grater than just the number of bricks
	}
}

void PlayingState::display() {
    SDL_RenderClear(renderer->getRenderer());

    // TODO: loop through a SDL_
	renderer->drawBricks(bricks);
    renderer->drawPaddle(paddlePosition);
    renderer->drawBall(ballPosition);
	renderer->drawTopLine(health);

    SDL_RenderPresent(renderer->getRenderer());
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
    if(!active) {
        std::unique_ptr<GameState> nextState(new MainMenuState(renderer));
        return nextState;
    }
    // TODO: handle transition to next state (e.g. pause or exit/menu)
    return nullptr;
}