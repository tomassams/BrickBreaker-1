#ifndef BRICKBREAKER_INPUTMANAGER_H
#define BRICKBREAKER_INPUTMANAGER_H

#include <map>
#include <SDL.h>
#include "InputAction.h"

class InputManager{
public:
	InputAction handle();
private:
	SDL_Event event;
	void readEvent();
	bool isKeyPressed(SDL_Keycode key) { return keymap[key]; }
	std::map<int, bool> keymap;
	bool KeyStillDown() {return event.key.repeat != 0;}
};


#endif