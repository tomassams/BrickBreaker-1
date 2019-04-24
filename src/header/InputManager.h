#ifndef BRICKBRAKER_INPUTMANAGER_H
#define BRICKBRAKER_INPUTMANAGER_H

#include <map>
#include <SDL.h>

class InputManager{
public:
	int update();
	int handle(const SDL_Event &event);
private:
	SDL_Event event;
	void readEvent();
	void readEvent(const SDL_Event &event);
	bool isKeyPressed(SDL_Keycode key) { return keymap[key]; }
	std::map<int, bool> keymap;
	bool KeyStillDown() {return event.key.repeat != 0;}
	bool KeyStillDown(const SDL_Event &event) {return event.key.repeat != 0;}
};


#endif