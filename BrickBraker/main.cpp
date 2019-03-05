//
//  main.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/19/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include "GameManager.hpp"

GameManager GameManager;

int main(int argc, const char * argv[]) {
	
	GameManager.initalize();
	do {
		GameManager.playGame();
	} while(!GameManager.doWeHaveAWinner());
	
	GameManager.quiteGame();
	
	return 0;
}
