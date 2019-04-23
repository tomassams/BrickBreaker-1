#include "../header/GameManager.h"

void GameManager::initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

	if (window == nullptr)
	{
		std::cout << "Could not create window" << SDL_GetError() << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	mBall.setParams(HEIGHT, WIDTH);
	mPaddle.setParams(WIDTH);

	ballSurface = SDL_LoadBMP("../res/ball.bmp");
	if (ballSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

	paddleSurface = SDL_LoadBMP("../res/paddle.bmp");
	if (paddleSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

	brickSurface = SDL_LoadBMP("../res/brick_red.bmp");
	if (brickSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

	paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
	ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
	brickTexture = SDL_CreateTextureFromSurface(renderer, brickSurface);
	activateGame();
}

void GameManager::activateGame()
{
	mBricks.InitializeBricks();

	mPaddle.setPaddlePositions(WIDTH, HEIGHT);
	numberOfBrokeBricks = 0;
	winner = false;
	quite = false;
	mBall.reset();
}

void GameManager:: destroy()
{
	SDL_DestroyTexture(paddleTexture);
	SDL_DestroyTexture(ballTexture);
	SDL_DestroyTexture(brickTexture);

	SDL_FreeSurface(ballSurface);
	SDL_FreeSurface(paddleSurface);
	SDL_FreeSurface(brickSurface);

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
			mPaddle.moveLeft();
			break;

		case 2:
			mPaddle.moveRight();
			break;

		default:
			return;
	}
}

void GameManager:: updateBrickPositions(){
	for (int i = 0; i < Bricks::brickY; i++)
	{
		for (int j = 0; j < Bricks::brickX; j++)
		{
			if (mBricks.getBrick(i, j).isHit())
			{
				SDL_Rect brickRect = mBricks.getBrick(i, j).rect;
				brickRect.x = 300000;
				brickRect.y = 300000;
				SDL_RenderCopy(renderer, brickTexture, nullptr, &brickRect);
			}
			else
			{
				SDL_Rect brickRect = mBricks.getBrick(i, j).rect;
				SDL_RenderCopy(renderer, brickTexture, nullptr, &brickRect);
			}
		}
	}
}

void GameManager::playGame()
{
	activateGame();

	do {
		userInput();

		ballRect = mBall.moveBall(mPaddle.getPaddleY(), mPaddle.getPaddleX()); //TODO: Make thread?
		paddleRect = mPaddle.paddleRect(); //TODO: Make thread?

		if (mBall.isOutOfBounds()) { quite = true; }

		SDL_RenderCopy(renderer, paddleTexture, nullptr, &paddleRect);
		SDL_RenderCopy(renderer, ballTexture, nullptr, &ballRect);

		updateBrickPositions();

		if (mBricks.ballBrickCollision(ballRect))
		{
			numberOfBrokeBricks++;
			mBall.changeVelocityX();

			if (numberOfBrokeBricks == mBricks.numberOfBricks)
			{
				winner = true;
				quite = true;
			}
		}

		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(2);

	} while (!quite);
}