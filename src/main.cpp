#include "header/GameManager.h"
#include "header/GameMenu.h"

int main(int argc, char * argv[]) {

	GameManager game = GameManager();
	game.init();
	while(!game.gameEnded) {
		game.play();
	}
	game.quit();

}
