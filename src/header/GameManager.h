#ifndef BRICKBRAKER_GAMEMANAGER_H
#define BRICKBRAKER_GAMEMANAGER_H

#include <iostream>
#include <SDL.h>

#include "Ball.h"
#include "Bricks.h"
#include "InputManager.h"
#include "Paddle.h"
#include "Renderer.h"

class GameManager{

public:
	void playGame();
	bool doWeHaveAWinner() const {return winner;}
	void quiteGame();
	void initialize();

	void init();
	void play();
	void quit();
	bool gameEnded = false;

private:
    Renderer stateRenderer;

	void activateGame();
	void destroy();
	void userInput();

	bool quite = false;
	bool winner = false;
	int WIDTH = 800, HEIGHT = 600;
	int numberOfBrokeBricks = 0;

	void updateBrickPositions();

	InputManager input;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Surface *ballSurface;
	SDL_Texture *ballTexture;
	SDL_Rect ballRect;

	SDL_Surface *paddleSurface;
	SDL_Texture *paddleTexture;
	SDL_Rect paddleRect;

	SDL_Surface *brickSurface;
	SDL_Texture *brickTexture;

	Bricks mBricks;
	Paddle mPaddle;
	Ball mBall;


};

#endif
