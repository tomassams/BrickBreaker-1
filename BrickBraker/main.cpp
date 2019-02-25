//
//  main.cpp
//  BrickBraker
//
//  Created by Henrik Anthony Odden Sandberg on 2/19/19.
//  Copyright © 2019 Henrik Anthony Odden Sandberg. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "GameManager.hpp"

GameManager GameManager;

int main(int argc, const char * argv[]) {
	GameManager.initalize();
	GameManager.playGame();
	GameManager.quiteGame();
	return 0;
}
