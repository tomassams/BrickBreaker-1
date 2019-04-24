#ifndef BRICKBRAKER_INPUTMANAGER_H
#define BRICKBRAKER_INPUTMANAGER_H

#include <map>
#include <SDL.h>

class InputManager{
public:
	int update();
	int handle();
private:
	SDL_Event event;
	void readEvent();
	bool isKeyPressed(SDL_Keycode key) { return keymap[key]; }
	std::map<int, bool> keymap;
	bool KeyStillDown() {return event.key.repeat != 0;}
};


#endif