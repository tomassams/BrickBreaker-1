#include "../header/GameManager.h"

void GameManager:: initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Brick Braker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HIGHT, 0);

	if (window == nullptr)
	{
		std::cout << "Could not create window" << SDL_GetError() << std::endl;
		return;
	}

	_ball.settParam(HIGHT, WIDTH);
	_paddle.setParams(WIDTH);

	ball = SDL_LoadBMP("../../res/ball.bmp");
	paddle = SDL_LoadBMP("../../res/paddle.bmp");
	brick = SDL_LoadBMP("../../res/brick_red.bmp");

	renderer = SDL_CreateRenderer(window, -1, 0);

	paddleTexture = SDL_CreateTextureFromSurface(renderer, paddle);
	ballTexture = SDL_CreateTextureFromSurface(renderer, ball);
	bricktexture = SDL_CreateTextureFromSurface(renderer, brick);
	activateGame();
}

void GameManager::activateGame()
{
	_bricks.InitilizeBricks();

	_paddle.setPaddlePositions(WIDTH, HIGHT);
	numberOfBrockenBricks = 0;
	winner = false;
	quite = false;
	_ball.reset();
}

void GameManager:: destroy()
{
	SDL_DestroyTexture(paddleTexture);
	SDL_DestroyTexture(ballTexture);
	SDL_DestroyTexture(bricktexture);

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

		ballrect = _ball.moveBall(_paddle.getPaddleY(), _paddle.getPaddleX());
		paddleRect = _paddle.paddleRect();

		if (_ball.isOutOfBounds()) { quite = true; }

		SDL_RenderCopy(renderer, paddleTexture, nullptr, &paddleRect);
		SDL_RenderCopy(renderer, ballTexture, nullptr, &ballrect);

		for (int i = 0; i < _bricks.brickY; i++)
			for (int j = 0; j < _bricks.brickX; j++) {
				if (!_bricks.getBrick(i, j).isHit()) {
					SDL_Rect brickRect = _bricks.getBrick(i, j).rect;
					SDL_RenderCopy(renderer, bricktexture, NULL, &brickRect);
				} else {
					SDL_Rect brickRect = _bricks.getBrick(i, j).rect;
					brickRect.x = 300000;
					brickRect.y = 300000;
					SDL_RenderCopy(renderer, bricktexture, NULL, &brickRect);
				}
			}

		if (_bricks.ballBrickCollision(ballrect)) {
			numberOfBrockenBricks++;
			_ball.changeVelocityX();

			if (numberOfBrockenBricks == _bricks.numberOfBricks) {
				winner = true;
				quite = true;
			}
		}

		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(2);

	} while (!quite);
}