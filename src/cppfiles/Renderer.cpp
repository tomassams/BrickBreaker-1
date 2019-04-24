#include <iostream>
#include "../header/Renderer.h"

void Renderer::initialize() {

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == nullptr)
    {
        std::cout << "Could not create window" << SDL_GetError() << std::endl;
        return;
    }

    ballSurface = SDL_LoadBMP("../res/ball.bmp");
    if (ballSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

    paddleSurface = SDL_LoadBMP("../res/paddle.bmp");
    if (paddleSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

    brickSurface = SDL_LoadBMP("../res/brick_red.bmp");
    if (brickSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

    renderer = SDL_CreateRenderer(window, -1, 0);

    paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    brickTexture = SDL_CreateTextureFromSurface(renderer, brickSurface);
}

void Renderer::destroy() {
    SDL_DestroyTexture(paddleTexture);
    SDL_FreeSurface(paddleSurface);

    SDL_DestroyTexture(ballTexture);
    SDL_FreeSurface(ballSurface);

    SDL_DestroyWindow(window);
}

void Renderer::drawPaddle(SDL_Rect rect) {
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
}

void Renderer::drawBall(SDL_Rect rect) {
    SDL_RenderCopy(renderer, ballTexture, nullptr, &rect);
}

void Renderer::drawBrick(SDL_Rect rect) {
    SDL_RenderCopy(renderer, brickTexture, nullptr, &rect);
}

SDL_Renderer* Renderer::getRenderer() {
    return renderer;
}

void Renderer::drawBricks(Bricks &bricks) {
    for (int i = 0; i < bricks.brickY; i++)
    {
        for (int j = 0; j < bricks.brickX; j++)
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
                SDL_Rect brickRect = bricks.getBrick(i, j).rect;
                SDL_RenderCopy(renderer, brickTexture, nullptr, &brickRect);
            }
        }
    }
}
