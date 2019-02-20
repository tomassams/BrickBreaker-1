//
//  main.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/19/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

bool quite = false;

int WIDTH = 800, HIGHT = 600;

void eventHandler( SDL_Event event )
{
	SDL_PollEvent(&event);
	
	if (event.type == SDL_QUIT) quite = true;
	
}

int x = 10, y = 10, velx = 1, vely = 1;

SDL_Rect moveBall() {
	if (x == HIGHT-40 ||x == 0)
		velx = -velx;

	if (y == WIDTH-40 ||y == 0)
		vely = -vely;
	
	x = x + velx;
	y = y + vely;
	return {y, x, 40, 40};
}

int main(int argc, const char * argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Brick Braker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HIGHT, 0);
	
	if (window == NULL)
	{
		std::cout << "Could not create window" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Surface *ball = SDL_LoadBMP("ball.bmp");
	SDL_Surface *bk = SDL_LoadBMP("space.bmp");
	if (ball == NULL || bk == NULL) std::cout<< "Could not load the image. SDL Error: " << SDL_GetError() << std::endl;
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	
//	SDL_Texture *bkTexture = SDL_CreateTextureFromSurface(renderer, bk);
//	SDL_Rect bkrect = {0 , 0, WIDTH, HIGHT};
	
	
	
	SDL_Rect ballrect;
	SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(renderer, ball);
	
	
	
	SDL_Event event;
	
	do{
		eventHandler(event);
		ballrect = moveBall();
		
		//SDL_RenderCopy(renderer, bkTexture, NULL, &bkrect);
		SDL_RenderCopy(renderer, ballTexture, NULL, &ballrect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		
	} while (!quite);
	
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
