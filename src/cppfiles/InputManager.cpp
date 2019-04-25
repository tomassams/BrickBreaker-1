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

InputAction InputManager::handle()
{
	SDL_PollEvent(&event);
	readEvent();

	if (event.type == SDL_QUIT || isKeyPressed(SDLK_ESCAPE) ||isKeyPressed(SDL_QUIT))
		return QUIT_GAME;

	else if ((isKeyPressed(SDLK_LEFT) || isKeyPressed(SDLK_a)))
		return MOVE_LEFT;

	else if (isKeyPressed(SDLK_RIGHT) || isKeyPressed(SDLK_d))
		return MOVE_RIGHT;

	else
		return NOTHING;
}