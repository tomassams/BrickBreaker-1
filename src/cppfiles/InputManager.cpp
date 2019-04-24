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

int InputManager:: update()
{
	SDL_PollEvent(&event);
	readEvent();

	if (event.type == SDL_QUIT || isKeyPressed(SDLK_ESCAPE) ||isKeyPressed(SDL_QUIT))
		return 0;

	else if ((isKeyPressed(SDLK_LEFT) || isKeyPressed(SDLK_a)))
		return 1;

	else if (isKeyPressed(SDLK_RIGHT) || isKeyPressed(SDLK_d))
		return 2;

	else
		return 100;
}

int InputManager::handle(const SDL_Event &event) {
	readEvent(event);

	if (event.type == SDL_QUIT || isKeyPressed(SDLK_ESCAPE) ||isKeyPressed(SDL_QUIT))
		return 0;

	else if ((isKeyPressed(SDLK_LEFT) || isKeyPressed(SDLK_a)))
		return 1;

	else if (isKeyPressed(SDLK_RIGHT) || isKeyPressed(SDLK_d))
		return 2;

	else if (isKeyPressed(SDLK_SPACE))
		return 3;

	else
		return 100;
}

void InputManager::readEvent(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN)
	{
		if (KeyStillDown(event)) return;

		keymap[event.key.keysym.sym] = true;
	}

	if (event.type == SDL_KEYUP)
		keymap[event.key.keysym.sym] = false;
}
