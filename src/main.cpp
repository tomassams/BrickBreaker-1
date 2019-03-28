#include "header/GameManager.h"

GameManager GameManager;
int main(int argc, const char * argv[]) {

	GameManager.initialize();
	do {
		GameManager.playGame();
	} while(!GameManager.doWeHaveAWinner());

	GameManager.quiteGame();

	return 0;
}
