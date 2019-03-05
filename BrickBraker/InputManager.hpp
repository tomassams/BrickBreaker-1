//
//  InputManager.hpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/24/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp
#include <map>
#include <SDL2/SDL.h>

class InputManager{
public:
	int update();
	
private:
	SDL_Event event;
	void readEvent();
	bool isKeyPressed(SDL_Keycode key) { return keymap[key]; }
	std::map<int, bool> keymap;
	bool KeyStillDown() {return event.key.repeat != 0;}
};


#endif /* InputManager_hpp */
