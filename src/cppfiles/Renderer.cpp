#include "../header/Renderer.h"

void Renderer::initialize()
{
    SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
    FONT_LARGE = TTF_OpenFont("../res/fonts/DIGDUG.ttf", 100);
    FONT_SMALL =  TTF_OpenFont("../res/fonts/barcadbold.ttf", 50);
    FONT_SCORE =  TTF_OpenFont("../res/fonts/digital-7.ttf", 28);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Could not initialize SDL Images: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (window == nullptr) {
        std::cout << "Could not create window" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Renderer::initializeMainMenu()
{
    // initialize the game title
    titleSurface = TTF_RenderText_Solid(FONT_LARGE, "BRICKBREAKER", COLOR_WHITE);
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
    int positioningHeight = HEIGHT / 3;

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
            positioningHeight + menuItemHeight*2,
            menuItems[1],
            menuItems[0 + 1]
    };

}

void Renderer::drawMenuItems(int highlightedItem)
{

    if(highlightedItem == 0)
    {
        menuItemOne = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_GREEN);
        menuItemTwo = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_WHITE);
    } else {
        menuItemOne = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_WHITE);
        menuItemTwo = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_GREEN);
    }
	menuItemOneTexture = SDL_CreateTextureFromSurface(renderer, menuItemOne);
	menuItemTwoTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwo);

    SDL_RenderCopy(renderer, menuItemOneTexture, nullptr, &firstOptionPosition);
    SDL_RenderCopy(renderer, menuItemTwoTexture, nullptr, &secondOptionPosition);
}

void Renderer::drawMenuTitle()
{
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titlePosition);
};

void Renderer::initializeGame()
{
    ballSurface = IMG_Load("../res/images/ballBlue.png");
    paddleSurface = IMG_Load("../res/images/paddleRed.png");
	hartSurface = IMG_Load("../res/images/health.png");

    if (paddleSurface == nullptr || ballSurface == nullptr || hartSurface == nullptr)
	{
		std::cout << "SDL_Image Error: " << SDL_GetError() << std::endl;
		return;
	}

    brickSurfaceVector.push_back(IMG_Load("../res/images/rectGreen.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectBlue.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectYellow.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectRed.png"));
	brickSurfaceVector.push_back(IMG_Load("../res/images/rectPurple.png"));

    std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [this](SDL_Surface* surface)
    {
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

void Renderer:: drawBricks(Bricks &bricks)
{
    auto brickVector = bricks.getBricks();
    std::for_each(brickVector->begin(), brickVector->end(), [this](Brick brick)
    {
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


void Renderer:: drawBrick(int health, SDL_Rect rect)
{
    SDL_RenderCopy(
            renderer,
            brickTextureVector.at((health <= 0) ? 0 : health-1), //Make sure health is never less then 0
            nullptr,
            &rect
    );
}


void Renderer:: drawPaddle(SDL_Rect rect)
{
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
}

void Renderer:: drawBall(SDL_Rect rect)
{
    SDL_RenderCopy(renderer, ballTexture, nullptr, &rect);
}

void Renderer:: drawStatusBar(int health, int score, Status status)
{
    for (int i = 0; i < health; i++)
    {
        SDL_Rect rect = {WIDTH - (40 + (35 * i)) , 10, 22, 20};
        SDL_RenderCopy(renderer, hartTexture, nullptr, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, 43, WIDTH, 43);
        SDL_RenderDrawLine(renderer, 0, 44, WIDTH, 44);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }

    SDL_Surface* scoreTxtSurface = TTF_RenderText_Solid(FONT_SCORE, std::to_string(score).c_str(), COLOR_GREEN);
    SDL_Texture* scoreTxtTexture = SDL_CreateTextureFromSurface(renderer, scoreTxtSurface);
    SDL_Rect scoreTxtPosition = { 10, 10, scoreTxtSurface->clip_rect.w, scoreTxtSurface->clip_rect.h, };

    std::string statusText;
    switch(status) {
        case INITIALIZED:
            statusText = "PRESS SPACE TO PLAY";
            break;
        case PAUSED:
            statusText = "GAME PAUSED - SPACE TO RESUME";
            break;
        case PLAYING:
            statusText = "GAME ACTIVE - SPACE TO PAUSE";
            break;
        case GAME_WON:
            statusText = "YOU WON! SPACE TO SEE MAIN MENU";
            break;
        case GAME_LOST:
            statusText = "YOU LOSE! SPACE TO SEE MAIN MENU";
            break;
        default:
            statusText = "";
            break;
    }

    SDL_Surface* gameStatusTxtSurface = TTF_RenderText_Solid(FONT_SCORE, statusText.c_str(), COLOR_GREEN);
    SDL_Texture* gameStatusTxtTexture = SDL_CreateTextureFromSurface(renderer, gameStatusTxtSurface);
    SDL_Rect gameStatusTxtPosition = { WIDTH / 2 - (gameStatusTxtSurface->clip_rect.w / 2) , 10, gameStatusTxtSurface->clip_rect.w, gameStatusTxtSurface->clip_rect.h, };

    SDL_RenderCopy(renderer, scoreTxtTexture, nullptr, &scoreTxtPosition);
    SDL_RenderCopy(renderer, gameStatusTxtTexture, nullptr, &gameStatusTxtPosition);
}

void Renderer:: destroyGame()
{
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);

	SDL_FreeSurface(ballSurface);
	SDL_FreeSurface(paddleSurface);
	SDL_FreeSurface(hartSurface);

	brickSurfaceVector.clear();
	brickTextureVector.clear();

    std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [](SDL_Surface* surface){
        SDL_FreeSurface(surface);
    });

    std::for_each(brickTextureVector.begin(), brickTextureVector.end(), [](SDL_Texture* texture){
        SDL_DestroyTexture(texture);
    });
}

void Renderer:: destroyMainMenu()
{
	SDL_FreeSurface(menuItemOne);
	SDL_FreeSurface(menuItemTwo);
	SDL_DestroyTexture(menuItemOneTexture);
	SDL_DestroyTexture(menuItemTwoTexture);
}

void Renderer:: destroy()
{
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}