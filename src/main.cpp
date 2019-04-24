#include "header/GameManager.h"

//GameManager GameManager;
int main(int argc, char * argv[]) {

	//GameManager.initialize();
	//do {
	//	GameManager.playGame();
	//} while(!GameManager.doWeHaveAWinner());
	//GameManager.quiteGame();

	GameManager game = GameManager();

	game.init();

	while(!game.gameEnded) {
		game.play();
	}

	game.quit();

	return 0;
}
