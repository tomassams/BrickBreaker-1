//
//  main.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/19/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "GameManager.hpp"

GameManager GameManager;

int main(int argc, const char * argv[]) {
	GameManager.initalize();
	GameManager.playGame();
	GameManager.quiteGame();
	return 0;
}

//	SDL_Surface *bk = SDL_LoadBMP("space.bmp");
//	SDL_Texture *bkTexture = SDL_CreateTextureFromSurface(renderer, bk);
//	SDL_Rect bkrect = {0 , 0, WIDTH, HIGHT};

//SDL_Texture *battTexture = SDL_CreateTextureFromSurface(renderer, bk);


//		SDL_RenderCopy(renderer, bkTexture, NULL, &bkrect);
