//
//  InputManager.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/24/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp
#include <iostream>
#include "InputManager.hpp"
#include <SDL2/SDL.h>

class InputManager{
public:
	static InputManager& Instance(){
		static InputManager instance;
		return instance;
	}
	
	void update();
	bool isQuitting() const { return _quite; }
	Uint8 returnButton() const {return buttons;}
	
	// Keyboard.
	bool KeyDown(int iKeyIndex);
	bool KeyStillDown(int iKeyIndex);
	bool KeyUp(int iKeyIndex);
	bool KeyStillUp(int iKeyIndex);
	
	// Mouse.
	bool MouseDown(int iButton);
	bool MouseStillDown(int iButton);
	bool MouseUp(int iButton);
	bool MouseStillUp(int iButton);
	
private:
	InputManager();
	
	SDL_Event event;
	//SDL_Handle _handle;
	bool _quite = false;
	const Uint8* _keyStates = nullptr;
	
	// A pointer to SDL's internal key state array.
	// (Memory handled by SDL.)
	Uint8* keys;
	
	// Our own copy of last update's array.
	// NB! Memory handled dynamically by us!
	std::unique_ptr<Uint8> oldKeys;
	
	// Number of keys in the arrays above, for this // app. (Can vary depending on setup/hardware.) int keyCount;
	// Mouse pos x and y.
	int mouseX;
	int mouseY;
	
	// Mouse buttons pressed.
	Uint8 buttons;
	
	// Mouse buttons pressed last update.
	Uint8 oldButtons;
};


#endif /* InputManager_hpp */
