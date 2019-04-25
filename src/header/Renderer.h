#ifndef BRICKBREAKER_RENDERER_H
#define BRICKBREAKER_RENDERER_H

#include <SDL.h>
#include "Bricks.h"

class Renderer {
public:
    Renderer();
    void initialize();
	void initializeMainMenu();
    void initializeGame();

    void destroy();

    void drawPaddle(SDL_Rect rect);
    void drawBall(SDL_Rect rect);
    void drawBrick(int health, SDL_Rect rect);
    void drawBricks(Bricks &bricks);
	void drawTopLine(int health);

    SDL_Renderer* getRenderer();
private:
    int WIDTH = 800, HEIGHT = 600;
	std::vector<SDL_Surface*> brickSurfaceVector;
	std::vector<SDL_Texture*> brickTextureVector;

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Surface *ballSurface;
    SDL_Texture *ballTexture;

    SDL_Surface *paddleSurface;
    SDL_Texture *paddleTexture;

	SDL_Surface *hartSurface;
	SDL_Texture *hartTexture;
};
#endif
