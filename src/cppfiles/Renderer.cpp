#include <iostream>
#include <SDL_image.h>
#include "../header/Renderer.h"

void Renderer::initialize() {

    SDL_Init(SDL_INIT_VIDEO);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    	std::cout << "Could not initialize SDL Images: " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == nullptr)
    	std::cout << "Could not create window" << SDL_GetError() << std::endl;

    ballSurface = IMG_Load("../res/images/ballBlue.png");
    if (ballSurface == nullptr)
    	std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

    paddleSurface = IMG_Load("../res/images/paddleRed.png");
    if (paddleSurface == nullptr)
    	std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;



    renderer = SDL_CreateRenderer(window, -1, 0);

    paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
}

void Renderer::destroy() {
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(brickTexture);

    SDL_FreeSurface(ballSurface);
    SDL_FreeSurface(paddleSurface);
    SDL_FreeSurface(brickSurface);

    SDL_DestroyWindow(window);
}

void Renderer:: drawPaddle(SDL_Rect rect) {
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
}

void Renderer:: drawBall(SDL_Rect rect) {
    SDL_RenderCopy(renderer, ballTexture, nullptr, &rect);
}

void Renderer:: drawBrick(SDL_Rect rect) {
    SDL_RenderCopy(renderer, brickTexture, nullptr, &rect);
}

SDL_Renderer* Renderer:: getRenderer() {
    return renderer;
}

void Renderer:: drawBricks(Bricks &bricks) {
    for (int i = 0; i < Bricks::brickY; i++)
    {
        for (int j = 0; j < Bricks::brickX; j++)
        {
            if (bricks.getBrick(i, j).isHit())
            {
                SDL_Rect brickRect = bricks.getBrick(i, j).rect;
                brickRect.x = 300000;
                brickRect.y = 300000;
                SDL_RenderCopy(renderer, brickTexture, nullptr, &brickRect);
            }
            else
            {
            	Brick brick = bricks.getBrick(i, j);
                SDL_Rect brickRect = brick.rect;
				swapBrickImage(brick.getHealth());
                SDL_RenderCopy(renderer, brickTexture, nullptr, &brickRect);
            }
        }
    }
}

void Renderer:: swapBrickImage(int brickHealth)
{
	SDL_FreeSurface(brickSurface);
	switch (brickHealth)
	{
		case 1:
			brickSurface = IMG_Load("../res/images/rectGreen.png");
			break;
		case 2:
			brickSurface = IMG_Load("../res/images/rectBlue.png");
			break;
		case 3:
			brickSurface = IMG_Load("../res/images/rectYellow.png");
			break;
		case 4:
			brickSurface = IMG_Load("../res/images/rectRed.png");
			break;
		default:
			brickSurface = IMG_Load("../res/images/rectPurp.png");
	}
	if (brickSurface == nullptr)
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

	brickTexture = SDL_CreateTextureFromSurface(renderer, brickSurface);
}
