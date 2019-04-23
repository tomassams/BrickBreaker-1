#include "header/GameManager.h"
#include "header/GameMenu.h"

GameManager GameManager;
GameMenu menu;
int main(int argc, char * argv[]) {
	int selectedFromMenu = menu.displayMenu();

	if (selectedFromMenu == 1){
		GameManager.initialize();
		do {
			GameManager.playGame();
		} while(!GameManager.doWeHaveAWinner());
		GameManager.quiteGame();
	}
	return 0;
}
