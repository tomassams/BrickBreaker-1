//
//  InputManager.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/24/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//
#include "InputManager.hpp"

void InputManager::update(){
	_keyStates = SDL_GetKeyboardState(0);
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch(event.type)
			{
				case SDL_QUIT:
					_quite = true;
					break;
					
				case SDLK_ESCAPE:
					_quite = true;
					break;
					
				case SDLK_LEFT:
					//TODO:- Set keyPress to move left
					break;
					
				case SDLK_RIGHT:
					//TODO:- Set keyPress to move Right
					break;
					
				default:
					//TODO:- Set keypress to empty
					return;
			}
		}
	}
}
