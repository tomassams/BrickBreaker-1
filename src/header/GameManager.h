#ifndef BRICKBRAKER_GAMEMANAGER_H
#define BRICKBRAKER_GAMEMANAGER_H

#include <iostream>
#include <SDL.h>
#include "Ball.h"
#include "Bricks.h"
#include "InputManager.h"
#include "Paddle.h"

class GameManager{

public:
	void playGame();
	bool doWeHaveAWinner() const {return winner;}
	void initialize();
	void quiteGame();

private:
	void activateGame();
	void destroy();
	void userInput();
	bool quite = false;
	bool winner = false;
	int WIDTH = 800, HIGHT = 600;
	int numberOBrokeBricks = 0;
	InputManager input;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Surface *ball;
	SDL_Texture *ballTexture;
	SDL_Rect ballRect;

	SDL_Surface *paddle;
	SDL_Texture *paddleTexture;
	SDL_Rect paddleRect;

	SDL_Surface *brick;
	SDL_Texture *brickTexture;

	Bricks _bricks;
	Paddle _paddle;
	Ball _ball;
};

#endif
