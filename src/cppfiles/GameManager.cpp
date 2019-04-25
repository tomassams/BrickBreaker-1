#include "../header/GameManager.h"

void GameManager::init()
{
	renderer->initialize();
}

void GameManager::play()
{
	std::unique_ptr<GameState> currentState(new MainMenuState(renderer));

	while(currentState->isActive()) {

		currentState->handleEvent();
		currentState->update();
		currentState->display();

		SDL_Delay(2);

		std::unique_ptr<GameState> nextState = currentState->nextState();
		if(nextState) {
			SDL_Delay(150);
			std::swap(currentState, nextState);
		}

	}

	gameEnded = true;
}

void GameManager::quit()
{
	renderer->destroy();
}

