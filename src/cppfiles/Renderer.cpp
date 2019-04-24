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

	brickSurfaceVector.clear();
	brickSurfaceVector.push_back(IMG_Load("../res/images/rectGreen.png"));
	brickSurfaceVector.push_back(IMG_Load("../res/images/rectBlue.png"));
	brickSurfaceVector.push_back(IMG_Load("../res/images/rectYellow.png"));
	brickSurfaceVector.push_back(IMG_Load("../res/images/rectRed.png"));
	brickSurfaceVector.push_back(IMG_Load("../res/images/rectPurp.png"));

	renderer = SDL_CreateRenderer(window, -1, 0);

	brickTextureVector.clear();
	std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [this](auto surface){
		brickTextureVector.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	});

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

	std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [](auto surface){
		SDL_FreeSurface(surface);
	});

	std::for_each(brickTextureVector.begin(), brickTextureVector.end(), [](auto texture){
		SDL_DestroyTexture(texture);
	});

    SDL_DestroyWindow(window);
}

void Renderer:: drawPaddle(SDL_Rect rect) {
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
}

void Renderer:: drawBall(SDL_Rect rect) {
    SDL_RenderCopy(renderer, ballTexture, nullptr, &rect);
}

void Renderer:: drawBrick(int health, SDL_Rect rect) {
	SDL_RenderCopy(renderer,
			brickTextureVector.at((health > 0) ? health-1 : 0),
			nullptr, &rect);
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
				int health = bricks.getBrick(i, j).getHealth();
				drawBrick(health, brickRect);
            }
            else
            {
				SDL_Rect brickRect = bricks.getBrick(i, j).rect;
				int health = bricks.getBrick(i, j).getHealth();
				drawBrick(health, brickRect);
            }
        }
    }
}
