#include "../header/GameMenu.h"

int GameMenu:: displayMenu()
{
	//TODO: Remove all non specific for menu
	bool quit = false;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_CreateWindow("SDL_ttf in SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	renderer = SDL_CreateRenderer(screen, -1, 0);

	TTF_Init();
	largeFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);
	smallFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 50);

	//SDL_GetWindowSize(screen, &width, &height);

	// CREATE TITLE TEXT
	titleSurface = TTF_RenderText_Solid(largeFont,"Brick Breaker", color[0]);
	titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
	SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);
	titleRect = { width/2 - titleSurface->w/2, titleSurface->h - height/6, titleWidth, titleHeight };

	//CREATE MENU OPTIONS
	for (int i = 0; i < options; i++)
		updateMenuContent(i, 0);

	do {
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
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
						destroy();
						return (i == 0) ? 1 : 0;
					}
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE){ break; }
		}
		renderAndPresent();
	} while (!quit);

	destroy();
	return 0;
}

bool GameMenu:: isMouseOnItem(int position)
{
	return x >= rectPosition[position].x
		   && x <= rectPosition[position].x + rectPosition[position].w
		   && y >= rectPosition[position].y
		   && y <= rectPosition[position].y + rectPosition[position].h;
}

void GameMenu:: renderAndPresent()
{
	SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
	SDL_RenderCopy(renderer, menuTexture[0], nullptr, &rectPosition[0]);
	SDL_RenderCopy(renderer, menuTexture[1], nullptr, &rectPosition[1]);
	SDL_RenderPresent(renderer);
}

void GameMenu:: updateMenuContent(int position, int newColor)
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

void GameMenu:: destroy()
{
	TTF_CloseFont(largeFont);
	TTF_CloseFont(smallFont);
	SDL_FreeSurface(titleSurface);
	SDL_DestroyTexture(titleTexture);
	for (int i = 0; i < options; i++) {
		SDL_FreeSurface(menu[i]);
		SDL_DestroyTexture(menuTexture[i]);
	}
	TTF_Quit();

	//TODO: Remove
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();
}