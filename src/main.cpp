#include "header/GameManager.h"
#include "header/GameMenu.h"

GameManager GameManager;
GameMenu menu;
int main(int argc, char * argv[]) {
	int play = menu.displayMenu();

	std::cout << "CODE: ";
	std::cout << play << std::endl;

	/*
	GameManager.initialize();
	do {
		GameManager.playGame();
	} while(!GameManager.doWeHaveAWinner());
	GameManager.quiteGame();
	*/
	return 0;
}
