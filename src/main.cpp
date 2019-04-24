#include "header/GameManager.h"
#include "header/GameMenu.h"

GameManager GameManager;
GameMenu menu;
//GameManager GameManager;

int main(int argc, char * argv[]) {

//	int selectedFromMenu = menu.displayMenu();

//	if (selectedFromMenu == 1){
//		GameManager.initialize();
//		do {
//			GameManager.playGame();
//		} while(!GameManager.doWeHaveAWinner());
//		GameManager.quiteGame();
//	}

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
