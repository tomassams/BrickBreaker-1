//
// Created by ts on 4/24/2019.
//

#include "../header/MainMenuState.h"
#include "../header/PlayingState.h"

MainMenuState::MainMenuState(std::shared_ptr<Renderer> r) {
    SDL_Log("MainMenuState() constructor called");

    r.get()->initializeMainMenu();

    sRenderer = r;

    renderer = sRenderer->getRenderer();

    TTF_Init();
    largeFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);
    smallFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 50);

    //SDL_GetWindowSize(screen, &width, &height); //TODO: This function updated width & height should be in loop

    // CREATE TITLE TEXT
    titleSurface = TTF_RenderText_Solid(largeFont,"Brick Breaker", color[0]);
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);
    titleRect = { width/2 - titleSurface->w/2, titleSurface->h - height/6, titleWidth, titleHeight };

    //CREATE MENU OPTIONS
    for (int i = 0; i < options; i++)
        updateMenuContent(i, 0);

}

MainMenuState::~MainMenuState() {
    SDL_Log("destructor called");
    SDL_Quit();
//
//    TTF_CloseFont(largeFont);
//    TTF_CloseFont(smallFont);
//    SDL_FreeSurface(titleSurface);
//    SDL_DestroyTexture(titleTexture);
//    for (int i = 0; i < options; i++) {
//        SDL_FreeSurface(menu[i]);
//        SDL_DestroyTexture(menuTexture[i]);
//    }
//    TTF_Quit();

};

void MainMenuState::update() {

}

void MainMenuState::display() {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_RenderCopy(renderer, menuTexture[0], nullptr, &rectPosition[0]);
    SDL_RenderCopy(renderer, menuTexture[1], nullptr, &rectPosition[1]);

    SDL_RenderPresent(renderer);
}

void MainMenuState::handleEvent() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                active = false;
                break;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for(int i = 0; i < options; i += 1)
                {
                    if (isMouseOnItem(i))
                    {
                        if (!selected[i])
                        {
                            selected[i] = true;
                            updateMenuContent(i, 1);
                        }
                    } else {
                        selected[i] = false;
                        updateMenuContent(i, 0);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < options; i++) {
                    if (isMouseOnItem(i))
                    {
                        selectedItem = (i == 0) ? 1 : 0;
                    }
                }
                break;
            default: break;
        }
    }

}

std::unique_ptr<GameState> MainMenuState::nextState() {

    if(selectedItem == 1) {
        SDL_Log("Triggering new game!");
        std::unique_ptr<GameState> nextState(new PlayingState(sRenderer));
        return nextState;
    } else if(selectedItem == -1) {
        SDL_Log("Triggering exit!");
        this->MainMenuState::~MainMenuState();
    }

    return nullptr;
}

bool MainMenuState::isActive() {
    return active;
}

bool MainMenuState:: isMouseOnItem(int position)
{
    return x >= rectPosition[position].x
           && x <= rectPosition[position].x + rectPosition[position].w
           && y >= rectPosition[position].y
           && y <= rectPosition[position].y + rectPosition[position].h;
}

void MainMenuState:: updateMenuContent(int position, int newColor)
{

    menu[position] = TTF_RenderText_Solid(smallFont, labels[position], color[newColor]);
    menuTexture[position] = SDL_CreateTextureFromSurface(renderer, menu[position]);

    // Adds an extra one in order to access the correct item in array when drawing menu item bigger then the first.
    // This should be scalable if we one day want to add a High score screen as well.
    const int extra = (position == 0) ? 0 : 1;

    // This is the only difference between the two menu items when it comes to position on the screen is that
    // one of the items need to add and the other needs to subtract clip rect height.
    const int clipRectHeight = menu[position]->clip_rect.h;
    const int positioningHeight = (position == 0) ? height/2 - clipRectHeight : height/2 + clipRectHeight;

    SDL_QueryTexture (
            menuTexture[position],
            nullptr, nullptr,
            &menuItems[position + extra],
            &menuItems[position + 1 + extra]
    );

    rectPosition[position] = {
            width/2 - menu[position]->clip_rect.w / 2,
            positioningHeight,
            menuItems[position + extra],
            menuItems[position + 1 + extra]
    };
}