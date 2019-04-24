#ifndef BRICKBREAKER_GAMEMENU_H
#define BRICKBREAKER_GAMEMENU_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

class GameMenu{
public:
	int displayMenu();

private:
	static const int options = 2;
	const char* labels[options] = {"Play Game","Exit"};
	int width = 800, height = 600, x, y;
	bool selected[options] = {false, false};
	int titleWidth = 0, titleHeight = 0;
	int menuItems[4] = {0,0,0,0};

	//TODO: Remove
	SDL_Window *screen;
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
	void renderAndPresent();
	void updateMenuContent(int position, int newColor);
	void destroy();
};
#endif
