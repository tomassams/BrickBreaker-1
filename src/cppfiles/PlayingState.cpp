#include <SDL.h>
#include "../header/PlayingState.h"

PlayingState::PlayingState(std::shared_ptr<Renderer> r) {
    SDL_Log("PlayingState() constructor called");
    exitToMenu = false;
    renderer = std::move(r);

    paddle = Paddle();
    ball = Ball();
    bricks = Bricks();

    renderer->initializeGame();

    int topOfGameScreen = 800/100*6;
    paddle.setParams(800);
    paddle.setPaddlePositions(800, 600);
    ball.setParams(600, 800);
    bricks.InitializeBricks(topOfGameScreen);

}

PlayingState::~PlayingState() = default;;

void PlayingState:: update()
{
    if(paused) {
        return;
    }

	paddlePosition = { paddle.getPaddleX(), paddle.getPaddleY(), 80, 26 };

	collisionManager.collision(&ball, paddlePosition, bricks.getBricks());
	ballPosition = ball.moveBall();

    if (ball.isOutOfBounds())
    {
        if (--health == 0)
		{
			exitToMenu = true;
			display();
		} else {
			ball.setBallStartPosition();
		}
	}
}

void PlayingState:: display()
{
    SDL_RenderClear(renderer->getRenderer());

    renderer->drawBricks(bricks);
    renderer->drawPaddle(paddlePosition);
	renderer->drawBall(ballPosition);
	renderer->drawTopLine(health);

    SDL_RenderPresent(renderer->getRenderer());
}

void PlayingState::handleEvent()
{
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

// temp
bool PlayingState::isActive()
{
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