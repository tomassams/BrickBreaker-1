#include <SDL.h>
#include "../header/PlayingState.h"

PlayingState::PlayingState(std::shared_ptr<Renderer> r) {
    exitToMenu = false;

    renderer = std::move(r);
    renderer->initializeGame();

    paddle.setParams(renderer->getWindowWidth());
    paddle.setPaddlePositions(renderer->getWindowWidth(), renderer->getWindowHeight());
    ball.initialize(600, 800);

    // we leave room at the top for a statusbar
    int topOfGameScreen = renderer->getWindowWidth() / 100 * 6;
    bricks.InitializeBricks(topOfGameScreen);

    // run update to render everything once
    status = PLAYING;
    update();
    status = INITIALIZED;
}

PlayingState::~PlayingState() = default;;

void PlayingState:: update()
{
    if(collisionManager.brickCollisions() == 135) {
        status = GAME_WON;
        return;
    }
    if(status != PLAYING) {
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
			ball.setStartingPosition();
		}
	}
}

void PlayingState:: display()
{

    SDL_RenderClear(renderer->getRenderer());

    renderer->drawBricks(bricks);
    renderer->drawPaddle(paddlePosition);
	renderer->drawBall(ballPosition);
	renderer->drawStatusBar(health, collisionManager.brickCollisions()*100, status);

    SDL_RenderPresent(renderer->getRenderer());

}

void PlayingState::handleEvent()
{

    switch(inputManager.handle()) {
        case QUIT_GAME:
            exitToMenu = !exitToMenu;
            break;
        case MOVE_LEFT:
            if(status == PLAYING)
            paddle.moveLeft();
            break;
        case MOVE_RIGHT:
            if(status == PLAYING)
            paddle.moveRight();
            break;
        case TOGGLE_PAUSE:
            if(status == GAME_WON) {
                exitToMenu = true;
            } else if(status != PLAYING) {
                SDL_Log("TOGGLE_PAUSE");
                status = PLAYING;
            } else {
                status = PAUSED;
            }
            break;
        default:
            return;
    }
}

std::unique_ptr<GameState> PlayingState::nextState() {

    if(exitToMenu) {
        std::unique_ptr<GameState> nextState(new MainMenuState(renderer));
        renderer->destroyGame();

        return nextState;
    }

    return nullptr;
}