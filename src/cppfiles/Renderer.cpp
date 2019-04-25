#include <iostream>
#include <SDL_image.h>
#include "../header/Renderer.h"

Renderer::Renderer() {
    SDL_Log("Renderer() constructor called");
}

void Renderer::initialize() {
    SDL_Log("Renderer initialize() method called");

    SDL_Init(SDL_INIT_VIDEO);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    	std::cout << "Could not initialize SDL Images: " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == nullptr)
    	std::cout << "Could not create window" << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, 0);

}

void Renderer::initializeMainMenu() {

}

void Renderer::initializeGame() {

    ballSurface = IMG_Load("../res/images/ballBlue.png");
    paddleSurface = IMG_Load("../res/images/paddleRed.png");
	hartSurface = IMG_Load("../res/images/health.png");

    if (paddleSurface == nullptr || ballSurface == nullptr || hartSurface == nullptr)
	{
		std::cout << "SDL_Image Error: " << SDL_GetError() << std::endl;
		return;
	}

	brickSurfaceVector.push_back(IMG_Load("../res/images/rectPurple.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectGreen.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectBlue.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectYellow.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectRed.png"));

    std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [this](auto surface){
		if (surface == nullptr)
		{
			std::cout << "SDL_Image Error: " << SDL_GetError() << std::endl;
			return;
		}
		brickTextureVector.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    });

    paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
	hartTexture = SDL_CreateTextureFromSurface(renderer, hartSurface);
}

void Renderer:: destroy() {
	SDL_DestroyTexture(paddleTexture);
	SDL_DestroyTexture(paddleTexture);
	SDL_DestroyTexture(hartTexture);

	std::for_each(brickTextureVector.begin(), brickTextureVector.end(), [](auto texture){
		SDL_DestroyTexture(texture);
	});

	std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [](auto surface){
		SDL_FreeSurface(surface);
	});

	SDL_FreeSurface(ballSurface);
	SDL_FreeSurface(paddleSurface);
	SDL_FreeSurface(hartSurface);

	brickSurfaceVector.clear();
	brickTextureVector.clear();

    SDL_DestroyWindow(window);
}

void Renderer:: drawPaddle(SDL_Rect rect) {
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
}

void Renderer:: drawBall(SDL_Rect rect) {
    SDL_RenderCopy(renderer, ballTexture, nullptr, &rect);
}

void Renderer:: drawBrick(int health, SDL_Rect rect) {
	SDL_RenderCopy(
			renderer,
			brickTextureVector.at(health),
			nullptr,
			&rect
	);
}

void Renderer:: drawTopLine(int health)
{
	for (int i = 0; i < health; i++)
	{
		SDL_Rect rect = {WIDTH - (40 + (35 * i)) , 10, 30, 28};
		SDL_RenderCopy(renderer, hartTexture, nullptr, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawLine(renderer, 0, 42, WIDTH, 42);
		SDL_RenderDrawLine(renderer, 0, 43, WIDTH, 43);
		SDL_RenderDrawLine(renderer, 0, 44, WIDTH, 44);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}
}

SDL_Renderer* Renderer:: getRenderer() {
    return renderer;
}

void Renderer:: drawBricks(Bricks &bricks) {
	auto brickVector = bricks.getBricks();
	std::for_each(brickVector.begin(), brickVector.end(), [this](Brick brick){
			SDL_Rect brickRect = brick.rect;

			if (brick.isHit())
			{
				brickRect.h = 0;
				brickRect.w = 0;
			}

			int health = brick.getHealth();
			drawBrick(health, brickRect);
	});
}
