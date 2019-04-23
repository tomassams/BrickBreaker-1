#ifndef BRICKBREAKER_GAMEMENU_H
#define BRICKBREAKER_GAMEMENU_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

class GameMenu{
public:
	int displayMenu();

private:
	int WIDTH = 800, HEIGHT = 600;
	static const int options = 2;
	SDL_Window *screen;
	SDL_Renderer *renderer;
	TTF_Font *font, *smallFont ;

	SDL_Surface *titleSurface;
	SDL_Texture *titleTexture;

	SDL_Surface* menu[options];
	SDL_Texture* menuTexture[options];

	void destroy();
};
#endif
