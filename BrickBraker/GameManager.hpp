//
//  GameManager.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/22/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "Ball.hpp"
#include "Bricks.hpp"
#include "InputManager.hpp"
#include "Paddle.hpp"


class GameManager{
	
	
public:
	void playGame();
	void eventHandler(SDL_Event event);
	void Destroy();
	void winning();
	void initalize();
	void quiteGame();
	
private:
	void destroy();
	void userInput();
	bool quite = false;
	int WIDTH = 800, HIGHT = 600;
	int numberOfBrockenBricks = 0;
	InputManager input;
	
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	SDL_Surface *ball;
	SDL_Texture *ballTexture;
	SDL_Rect ballrect;
	
	SDL_Surface *paddle;
	SDL_Texture *paddleTexture;
	SDL_Rect paddleRect;
	
	SDL_Surface *brick;
	SDL_Texture *bricktexture;
	
	Bricks _bricks;
	Paddle _paddle;
	Ball _ball;	
};

#endif /* GameManager_hpp */
