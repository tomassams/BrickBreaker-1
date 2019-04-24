#include "../header/GameManager.h"
#include "../header/GameState.h"
#include "../header/PlayingState.h"
#include "../header/MainMenuState.h"

void GameManager::init() {
	stateRenderer.initialize();
}

void GameManager::play() {

	bool running = true;
//    std::unique_ptr<GameState> currentState(new PlayingState(stateRenderer));
    std::unique_ptr<GameState> currentState(new MainMenuState(stateRenderer));

	while(running) {

		currentState->handleEvent();
		currentState->update();
		currentState->display(stateRenderer);

		SDL_Delay(2);


		std::unique_ptr<GameState> nextState = currentState->nextState();
//		std::unique_ptr<GameState> nextState(new PlayingState(stateRenderer));
		if(nextState || !currentState->isActive()) {
			running = false;
//			std::swap(currentState, nextState); // TODO
		}
	}

	gameEnded = true; // quit (TODO: handle swap states - pause / main menu)
}

void GameManager::quit() {
	stateRenderer.destroy();
    SDL_Quit();
}
