//
// Created by ts on 4/24/2019.
//

#include <iostream>
#include "../header/Renderer.h"

void Renderer::initialize(SDL_Rect rect) {

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == nullptr)
    {
        std::cout << "Could not create window" << SDL_GetError() << std::endl;
        return;
    }

    paddleSurface = SDL_LoadBMP("../res/paddle.bmp");
    if (paddleSurface == nullptr){ std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl; }

    renderer = SDL_CreateRenderer(window, -1, 0);

    paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
    SDL_RenderPresent(renderer);
}

void Renderer::destroy() {
    SDL_DestroyTexture(paddleTexture);
    SDL_FreeSurface(paddleSurface);

    SDL_DestroyWindow(window);
}

void Renderer::drawPaddle(SDL_Rect rect) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
    SDL_RenderPresent(renderer);
}

void Renderer::draw() {

}