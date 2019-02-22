//
//  GameManager.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include <iostream>
#include "GameManager.hpp"
#include <SDL2/SDL.h>
#include "Paddle.hpp"

void GameManager:: initalize()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Brick Braker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HIGHT, 0);
	
	if (window == NULL)
	{
		std::cout << "Could not create window" << SDL_GetError() << std::endl;
		return;
	}
	
	ball = SDL_LoadBMP("ball.bmp");
	paddle = SDL_LoadBMP("paddle.bmp");
	brick = SDL_LoadBMP("brick_red.bmp");
	
	if (ball == NULL) std::cout<< "Could not load the image. SDL Error: " << SDL_GetError() << std::endl;
	if (paddle == NULL) std::cout<< "Could not load the image. SDL Error: " << SDL_GetError() << std::endl;
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	paddleTexture = SDL_CreateTextureFromSurface(renderer, paddle);
	ballTexture = SDL_CreateTextureFromSurface(renderer, ball);
	bricktexture = SDL_CreateTextureFromSurface(renderer, brick);
	
	_bricks.InitilizeBricks();
	_paddle.setPaddlePositions(WIDTH, HIGHT);
	
}

void GameManager:: quiteGame()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameManager:: eventHandler( SDL_Event event )
{
	SDL_PollEvent(&event);
	
	if (event.type == SDL_QUIT) quite = true;
	
	else if (event.type==SDL_KEYDOWN){
		if (event.key.keysym.sym == SDLK_LEFT && _paddle.getPaddleX() > 0)
			_paddle.moveLeft();
		
		if (event.key.keysym.sym == SDLK_RIGHT && _paddle.getPaddleX() <= WIDTH-90)
			_paddle.moveRigth();
	}
	
}

void GameManager::playGame()
{
	do{
		eventHandler(event);
		
		ballrect = _ball.moveBall(HIGHT, WIDTH, _paddle.getPaddleY(), _paddle.getPaddleX());
		paddleRect = _paddle.paddleRect();
		
		SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);
		SDL_RenderCopy(renderer, ballTexture, NULL, &ballrect);
		
		for (int i = 0; i < _bricks.brickY; i++)
			for (int j = 0; j < _bricks.brickX; j++)
			{
				if (!_bricks.getBrick(i,j).isHit()){
					SDL_Rect brickRect = _bricks.getBrick(i,j).rect;
					SDL_RenderCopy(renderer, bricktexture, NULL, &brickRect);
				} else {
					SDL_Rect brickRect = _bricks.getBrick(i,j).rect;
					brickRect.x = 300000;
					brickRect.y = 300000;
					SDL_RenderCopy(renderer, bricktexture, NULL, &brickRect);
				}
			}
		
		if (_bricks.ballBrickCollision(ballrect)) {
			if ((rand() % 2) +1 == 1) _ball.changeVelocityX();;
			if ((rand() % 2) +1 == 1) _ball.changeVelocityY();
		}
		
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(4);
		
	} while (!quite);
}

//void Destroy()
//{
//	SDL_DelayTexture(Texturename);
//  SDL_FreeSurface(SurfeToFree);
//}

void winning()
{
	//SDL_Surface *win = SDL_LoadBMP();
	//SDL_Texture *winTexture = SDL_CreateTextureFromSurface(rendrer, <#SDL_Surface *surface#>)
	//	SDL_Rect winRect = {250, 200, 350, 350};
	//	SDL_RenderCopy(rendrer, winTexture, NULL, &winRect)
}
