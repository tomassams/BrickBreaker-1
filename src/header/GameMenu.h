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
	SDL_Window *screen;
	SDL_Renderer *renderer;
	TTF_Font *font;
	SDL_Surface *surface;
	SDL_Texture *texture;

	void destroy();
};
#endif
