#include <iostream>
#include <SDL_image.h>
#include "../header/Renderer.h"

Renderer::Renderer() {
}

void Renderer::initialize() {
    SDL_Init(SDL_INIT_VIDEO);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Could not initialize SDL Images: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (window == nullptr) {
        std::cout << "Could not create window" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Renderer::initializeMainMenu() {

    // initialize TTF package and fonts
    TTF_Init();
    FONT_LARGE = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);
    FONT_SMALL =  TTF_OpenFont("../res/arial/films.Dynasty.ttf", 50);

    // initialize the game title
    titleSurface = TTF_RenderText_Solid(FONT_LARGE, "Brick Breaker", COLOR_WHITE);
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

    // fetch the title texture width and height and make the rect
    SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);
    titlePosition = { WIDTH / 2 - titleSurface->w / 2, titleSurface->h - HEIGHT / 6, titleWidth, titleHeight };

    // initialize our two menu items
    menuItemOne = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_WHITE);
    menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);

    menuItemTwo = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_GREEN);
    menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);

    int menuItemHeight = menuItemOne->clip_rect.h;
    int positioningHeight = HEIGHT / 2;

    SDL_QueryTexture ( menuItemOneTexture, nullptr, nullptr, &menuItems[0], &menuItems[0 + 1] );
    SDL_QueryTexture ( menuItemTwoTexture, nullptr, nullptr, &menuItems[1], &menuItems[1 + 1] );

    firstOptionPosition = {
            WIDTH / 2 - menuItemOne->clip_rect.w / 2,
            positioningHeight,
            menuItems[0],
            menuItems[0 + 1]
    };
    secondOptionPosition = {
            WIDTH / 2 - menuItemTwo->clip_rect.w / 2,
            positioningHeight + menuItemHeight,
            menuItems[1],
            menuItems[1 + 1]
    };

}

void Renderer::drawMenuItems(int highlightedItem) {

    // TODO, possibly cleanup..
    if(highlightedItem == 0) {
        menuItemOne = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_GREEN);
        menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);
        menuItemTwo = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_WHITE);
        menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);
    } else{
        menuItemOne = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_WHITE);
        menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);
        menuItemTwo = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_GREEN);
        menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);
    }

    SDL_RenderCopy(renderer, menuItemOneTexture, nullptr, &firstOptionPosition);
    SDL_RenderCopy(renderer, menuItemTwoTexture, nullptr, &secondOptionPosition);
}

void Renderer::drawMenuTitle() {
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titlePosition);
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