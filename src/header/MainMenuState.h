//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_MAINMENUSTATE_H
#define BRICKBREAKER_MAINMENUSTATE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "GameState.h"
#include "InputManager.h"

class MainMenuState : public GameState {
public:
    MainMenuState(Renderer &renderer);
    ~MainMenuState();
    void update() override;
    void display(Renderer &renderer) override;
    void handleEvent() override;
    std::unique_ptr<GameState> nextState() override;
    bool isActive() override;

    int showMenu();
    int selectedItem;
private:
    Renderer sRenderer;
    InputManager inputManager;
    bool active = true;

    static const int options = 2;
    const char* labels[options] = {"Play Game","Exit"};
    int width = 800, height = 600, x, y;
    bool selected[options] = {false, false};
    int titleWidth = 0, titleHeight = 0;
    int menuItems[4] = {0,0,0,0};

    //TODO: Remove
    SDL_Renderer *renderer;
    TTF_Font *largeFont, *smallFont ;

    SDL_Color color[2] = {{255,255,255}, {141, 182, 0}};
    SDL_Surface *titleSurface;
    SDL_Texture *titleTexture;
    SDL_Rect titleRect;

    SDL_Surface* menu[options];
    SDL_Texture* menuTexture[options];
    SDL_Rect rectPosition[options];

    bool isMouseOnItem(int i);
    void updateMenuContent(int position, int newColor);
};


#endif //BRICKBREAKER_MAINMENUSTATE_H
