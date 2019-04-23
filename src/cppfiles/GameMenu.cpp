#include "../header/GameMenu.h"

int GameMenu::displayMenu()
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	screen = SDL_CreateWindow("SDL_ttf in SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(screen, -1, 0);


	font = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 100);
	smallFont = TTF_OpenFont("../res/arial/films.Dynasty.ttf", 50);

	int width, height, x, y;
	SDL_GetWindowSize(screen, &width, &height);

	const char* labels[options] = {"Play Game","Exit"};
	bool selected[options] = {false, false};

	SDL_Color color[2] = {{255,255,255},{255,0,0}};

	titleSurface = TTF_RenderText_Solid(font,"Brick Breaker", color[0]);
	titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

	int titleWidth = 0, titleHeight = 0, menuItemWidth = 0, menuItemHeight = 0;
	SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);

	//Sets position for title text
	SDL_Rect titleRect = { width/2 - titleSurface->w/2, titleSurface->h - height/6, titleWidth, titleHeight };

	menu[0] = TTF_RenderText_Solid(smallFont , labels[0], color[0]);
	menu[1] = TTF_RenderText_Solid(smallFont , labels[1], color[0]);
	menuTexture[0] = SDL_CreateTextureFromSurface(renderer, menu[0]);
	menuTexture[1] = SDL_CreateTextureFromSurface(renderer, menu[1]);
	SDL_QueryTexture(menuTexture[0], nullptr, nullptr, &menuItemWidth, &menuItemHeight);
	SDL_QueryTexture(menuTexture[1], nullptr, nullptr, &titleWidth, &titleHeight);

	SDL_Rect pos[options] = {
		{
			width/2 - menu[0]->clip_rect.w/2,
			height/2 - menu[0]->clip_rect.h,
			menuItemWidth,
			menuItemHeight
		},{
			width/2 - menu[1]->clip_rect.w/2,
			height/2 + menu[1]->clip_rect.h,
			titleWidth,
			titleHeight
		}
	};

	int menuItemSelected = 0;
	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				menuItemSelected = 0;
				break;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for(int i = 0; i < options; i += 1) {
					if(x>=pos[i].x
						&& x<=pos[i].x+pos[i].w
						&& y>=pos[i].y
						&& y<=pos[i].y+pos[i].h)
					{
						if(!selected[i])
						{
							selected[i] = true;
							SDL_FreeSurface(menu[i]);
							menu[i] = TTF_RenderText_Solid(smallFont,labels[i],color[1]);
						}
					}
					else
					{
						if(selected[i])
						{
							selected[i] = false;
							SDL_FreeSurface(menu[i]);
							menu[i] = TTF_RenderText_Solid(smallFont,labels[i], color[0]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (auto menuItem : pos) {
					if (x >= menuItem.x
						&& x <= menuItem.x + menuItem.w
						&& y >= menuItem.y
						&& y <= menuItem.y + menuItem.h)
					{
						SDL_FreeSurface(menu[0]);
						SDL_FreeSurface(menu[1]);
						return (menuItem.x == width/2 - menu[0]->clip_rect.w/2) ? 1 : 0;
					}
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_FreeSurface(menu[0]);
					SDL_FreeSurface(menu[1]);
					return 0;
				}
		}

		SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
		SDL_RenderCopy(renderer, menuTexture[0], nullptr, &pos[0]);
		SDL_RenderCopy(renderer, menuTexture[1], nullptr, &pos[1]);
		SDL_RenderPresent(renderer);
	}

	destroy();
	return menuItemSelected;
}

void GameMenu::destroy()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(titleTexture);
	SDL_FreeSurface(titleSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	TTF_Quit();
	SDL_Quit();
}