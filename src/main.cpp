#include "header/GameManager.h"

GameManager GameManager;
int main(int argc, char * argv[]) {

	GameManager.initialize();
	do {
		GameManager.playGame();
	} while(!GameManager.doWeHaveAWinner());
	GameManager.quiteGame();

	return 0;
}
