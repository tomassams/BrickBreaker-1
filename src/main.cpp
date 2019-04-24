#include "header/GameManager.h"

int main(int argc, char * argv[]) {

//	int selectedFromMenu = menu.displayMenu();

//	if (selectedFromMenu == 1){
		GameManager game = GameManager();
		game.init();
		while(!game.gameEnded) {
			game.play();
		}
		game.quit();
//	} else {
//		//TODO: Make sure everything is destroyed before we return
//	}

	//GameManager.initialize();
	//do {
	//	GameManager.playGame();
	//} while(!GameManager.doWeHaveAWinner());
	//GameManager.quiteGame();
}
