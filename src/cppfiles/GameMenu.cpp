#include "../header/GameMenu.h"

int GameMenu::displayMenu()
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	screen = SDL_CreateWindow("SDL_ttf in SDL2",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(screen, -1, 0);
	font = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 25);

	SDL_Color color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font,"Welcome to Gigi Labs", color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect rect = { 0, 0, texW, texH };

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
		}

		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_RenderPresent(renderer);
	}

	destroy();
	return 0;
}

void GameMenu::destroy()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	TTF_Quit();
	SDL_Quit();
}