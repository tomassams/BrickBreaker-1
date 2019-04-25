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

    TTF_Init();
    largeFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);
    smallFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 50);

    titleSurface = TTF_RenderText_Solid(largeFont,"Brick Breaker", COLOR_WHITE);
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

    // fetch title width & height
    SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);

    titleRect = { width/2 - titleSurface->w/2, titleSurface->h - height/6, titleWidth, titleHeight };

    menuItemOne = TTF_RenderText_Solid(smallFont, "New Game", COLOR_WHITE);
    menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);

    menuItemTwo = TTF_RenderText_Solid(smallFont, "Exit", COLOR_GREEN);
    menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);

    const int clipRectHeight1 = menuItemOne->clip_rect.h;
    const int clipRectHeight2 = menuItemTwo->clip_rect.h;
    const int positioningHeight1 = height / 2;
    const int positioningHeight2 = height / 2 + clipRectHeight2;

    SDL_QueryTexture (
            menuItemOneTexture,
            nullptr, nullptr,
            &menuItems[0],
            &menuItems[0 + 1]
    );

    SDL_QueryTexture (
            menuItemTwoTexture,
            nullptr, nullptr,
            &menuItems[1],
            &menuItems[1 + 1]
    );

    rectPositionOne = {
            width/2 - menuItemOne->clip_rect.w / 2,
            positioningHeight1,
            menuItems[0],
            menuItems[0 + 1]
    };

    rectPositionTwo = {
            width/2 - menuItemTwo->clip_rect.w / 2,
            positioningHeight2,
            menuItems[1],
            menuItems[1 + 1]
    };

}

void Renderer::drawMenuItems(int highlightedItem) {

    // TODO, possibly cleanup..
    if(highlightedItem == 0) {
        menuItemOne = TTF_RenderText_Solid(smallFont, "New Game", COLOR_GREEN);
        menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);
        menuItemTwo = TTF_RenderText_Solid(smallFont, "Exit", COLOR_WHITE);
        menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);
    } else{
        menuItemOne = TTF_RenderText_Solid(smallFont, "New Game", COLOR_WHITE);
        menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);
        menuItemTwo = TTF_RenderText_Solid(smallFont, "Exit", COLOR_GREEN);
        menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);
    }

    SDL_RenderCopy(renderer, menuItemOneTexture, nullptr, &rectPositionOne);
    SDL_RenderCopy(renderer, menuItemTwoTexture, nullptr, &rectPositionTwo);
}

void Renderer::drawMenuTitle() {
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
};

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

void Renderer::destroyGame() {
    SDL_Log("destroyGame() called from Renderer");
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
}
void Renderer::destroyMainMenu() {
    SDL_Log("destroyMainMenu() called from Renderer");
}

void Renderer::destroy() {
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