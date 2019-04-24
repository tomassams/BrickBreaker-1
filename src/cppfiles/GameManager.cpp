#include "../header/GameManager.h"
#include "../header/GameState.h"
#include "../header/PlayingState.h"
#include "../header/MainMenuState.h"

void GameManager::init() {
	stateRenderer.initialize();
}

void GameManager::play() {

	bool running = true;
	//std::unique_ptr<GameState> currentState(new PlayingState(stateRenderer));
	std::unique_ptr<GameState> currentState(new MainMenuState(stateRenderer));

	while(running) {

		currentState->handleEvent();
		currentState->update();
		currentState->display(stateRenderer);

		SDL_Delay(2);

		if(currentState->nextState()) {
			std::unique_ptr<GameState> nextState = currentState->nextState();
			SDL_Log("nextState swap happening");
			std::swap(currentState, nextState);
			SDL_Log("nextState swap happening2");
		}
	}

	gameEnded = true; // quit (TODO: handle swap states - pause / main menu)
}

void GameManager::quit() {
	stateRenderer.destroy();
    SDL_Quit();
}
