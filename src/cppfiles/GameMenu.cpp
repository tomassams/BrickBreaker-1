#include "../header/GameMenu.h"

int GameMenu::displayMenu()
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	screen = SDL_CreateWindow("SDL_ttf in SDL2",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(screen, -1, 0);


	font = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);

	int width, height;
	SDL_GetWindowSize(screen, &width, &height);

	SDL_Color color = { 255, 255, 255 };
	surface = TTF_RenderText_Solid(font,"Brick Breaker", color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 0, texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect rect = { width/2 - surface->w/2, surface->h-height/6, texW, texH };


	int menuItemSelected = 0;
	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				menuItemSelected = 1;
				break;
		}

		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_RenderPresent(renderer);
	}

	destroy();
	return menuItemSelected;
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