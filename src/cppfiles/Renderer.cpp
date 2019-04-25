#include <iostream>
#include <SDL_image.h>
#include "../header/Renderer.h"

Renderer::Renderer() {
    SDL_Log("Renderer() constructor called"); // TODO: remove after debug
}

void Renderer::initialize() {
    SDL_Log("Renderer initialize() method called"); // TODO: remove after debug

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

    SDL_FreeSurface(ballSurface);
    SDL_FreeSurface(paddleSurface);

	std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [](auto surface){
		SDL_FreeSurface(surface);
	});

	std::for_each(brickTextureVector.begin(), brickTextureVector.end(), [](auto texture){
		SDL_DestroyTexture(texture);
	});

    SDL_DestroyWindow(window);
    SDL_Quit();
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
			brickTextureVector.at((health > 0) ? health-1 : 0),
			nullptr,
			&rect
	);
}

SDL_Renderer* Renderer:: getRenderer() {
    return renderer;
}

void Renderer:: drawBricks(Bricks &bricks) {
	auto rickVector = bricks.getBricks();
	std::for_each(rickVector.begin(), rickVector.end(), [this](Brick brick){
			SDL_Rect brickRect = brick.rect;

			if (brick.isHit())
			{
				brickRect.x = 300000;
				brickRect.y = 300000;
			}

			int health = brick.getHealth();
			drawBrick(health, brickRect);
	});
}