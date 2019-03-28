#include "../header/GameManager.h"

void GameManager:: initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HIGHT, 0);

	if (window == nullptr)
	{
		std::cout << "Could not create window" << SDL_GetError() << std::endl;
		return;
	}


	_ball.settParam(HIGHT, WIDTH);
	_paddle.setParams(WIDTH);

	ball = SDL_LoadBMP("ball.bmp");
	if (ball == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

	paddle = SDL_LoadBMP("paddle.bmp");
	if (paddle == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

	brick = SDL_LoadBMP("brick_red.bmp");
	if (brick == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }



	renderer = SDL_CreateRenderer(window, -1, 0);

	paddleTexture = SDL_CreateTextureFromSurface(renderer, paddle);
	ballTexture = SDL_CreateTextureFromSurface(renderer, ball);
	brickTexture = SDL_CreateTextureFromSurface(renderer, brick);
	activateGame();
}

void GameManager::activateGame()
{
	_bricks.InitializeBricks();

	_paddle.setPaddlePositions(WIDTH, HIGHT);
	numberOBrokeBricks = 0;
	winner = false;
	quite = false;
	_ball.reset();
}

void GameManager:: destroy()
{
	SDL_DestroyTexture(paddleTexture);
	SDL_DestroyTexture(ballTexture);
	SDL_DestroyTexture(brickTexture);

	SDL_FreeSurface(ball);
	SDL_FreeSurface(paddle);
	SDL_FreeSurface(brick);

	SDL_DestroyWindow(window);
}

void GameManager:: quiteGame()
{
	destroy();
	SDL_Quit();
}

void GameManager:: userInput()
{
	switch (input.update())
	{
		case 0:
			quite = true;
			winner = true;
			break;

		case 1:
			_paddle.moveLeft();
			break;

		case 2:
			_paddle.moveRight();
			break;

		default:
			return;
	}
}

void GameManager::playGame()
{
	activateGame();
	do {
		userInput();

		ballRect = _ball.moveBall(_paddle.getPaddleY(), _paddle.getPaddleX());
		paddleRect = _paddle.paddleRect();

		if (_ball.isOutOfBounds()) { quite = true; }

		SDL_RenderCopy(renderer, paddleTexture, nullptr, &paddleRect);
		SDL_RenderCopy(renderer, ballTexture, nullptr, &ballRect);

		for (int i = 0; i < _bricks.brickY; i++)
			for (int j = 0; j < _bricks.brickX; j++) {
				if (!_bricks.getBrick(i, j).isHit()) {
					SDL_Rect brickRect = _bricks.getBrick(i, j).rect;
					SDL_RenderCopy(renderer, brickTexture, NULL, &brickRect);
				} else {
					SDL_Rect brickRect = _bricks.getBrick(i, j).rect;
					brickRect.x = 300000;
					brickRect.y = 300000;
					SDL_RenderCopy(renderer, brickTexture, NULL, &brickRect);
				}
			}

		if (_bricks.ballBrickCollision(ballRect)) {
			numberOBrokeBricks++;
			_ball.changeVelocityX();

			if (numberOBrokeBricks == _bricks.numberOfBricks) {
				winner = true;
				quite = true;
			}
		}

		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(2);

	} while (!quite);
}