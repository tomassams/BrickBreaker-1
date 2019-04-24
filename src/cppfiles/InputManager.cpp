#include "../header/InputManager.h"

void InputManager:: readEvent()
{
	if (event.type == SDL_KEYDOWN)
	{
		if (KeyStillDown()) return;
		keymap[event.key.keysym.sym] = true;
	}

	if (event.type == SDL_KEYUP)
		keymap[event.key.keysym.sym] = false;
}

InputAction InputManager::handle() {
	SDL_PollEvent(&event);
	readEvent();

	if (event.type == SDL_QUIT || isKeyPressed(SDLK_ESCAPE) ||isKeyPressed(SDL_QUIT))
		return QUIT_PROGRAM;

	else if ((isKeyPressed(SDLK_LEFT) || isKeyPressed(SDLK_a)))
		return LEFT_ARROW;

	else if (isKeyPressed(SDLK_RIGHT) || isKeyPressed(SDLK_d))
		return RIGHT_ARROW;

	else if(event.type == SDL_MOUSEMOTION)
		return MOUSE_MOVEMENT;

	else if(event.type == SDL_MOUSEBUTTONDOWN)
		return MOUSE_CLICK;

	else
		return NOTHING;
}
