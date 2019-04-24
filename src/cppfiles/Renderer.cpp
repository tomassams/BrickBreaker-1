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

    brickSurface = IMG_Load("../res/images/rectGreen.png");
    if (brickSurface == nullptr)
    	std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, 0);

    paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    brickTexture = SDL_CreateTextureFromSurface(renderer, brickSurface);
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
                SDL_Rect brickRect = bricks.getBrick(i, j).rect;
                SDL_RenderCopy(renderer, brickTexture, nullptr, &brickRect);
            }
        }
    }
}

void Renderer::showMainMenu() {
    static const int options = 2;
    const char* labels[options] = {"Play Game","Exit"};
    int width = 800, height = 600, x, y;
    bool selected[options] = {false, false};
    int titleWidth = 0, titleHeight = 0;
    int menuItems[4] = {0,0,0,0};

    TTF_Init();
    TTF_Font* largeFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);
    TTF_Font* smallFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 50);

    SDL_Color color[2] = {{255,255,255}, {141, 182, 0}};
    SDL_Surface *titleSurface;
    SDL_Texture *titleTexture;
    SDL_Rect titleRect;

    SDL_Surface* menu[options];
    SDL_Texture* menuTexture[options];
    SDL_Rect rectPosition[options];


    //SDL_GetWindowSize(screen, &width, &height); //TODO: This function updated width & height should be in loop

    // CREATE TITLE TEXT
    titleSurface = TTF_RenderText_Solid(largeFont,"Brick Breaker", color[0]);
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);
    titleRect = { width/2 - titleSurface->w/2, titleSurface->h - height/6, titleWidth, titleHeight };

}

void Renderer::destroyMainMnu() {
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(screen);
//    SDL_Quit();
}
