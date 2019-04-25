#ifndef BRICKBREAKER_RENDERER_H
#define BRICKBREAKER_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Bricks.h"

class Renderer {
public:
    Renderer();
    void initialize();
	void initializeMainMenu();
    void initializeGame();

    void destroy();
    void destroyMainMenu();
    void destroyGame();

    void drawPaddle(SDL_Rect rect);
    void drawBall(SDL_Rect rect);
    void drawBrick(int health, SDL_Rect rect);
    void drawBricks(Bricks &bricks);

    void drawMenuItems(int highlightedItem);
    void drawMenuTitle();

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

	TTF_Font *largeFont, *smallFont ;

	SDL_Color COLOR_WHITE = { 255, 255, 255 };
	SDL_Color COLOR_GREEN = { 141, 182, 0 };
	SDL_Color COLOR_BLACK = { 0, 0 , 0 };

	SDL_Surface *titleSurface;
	SDL_Texture *titleTexture;
	int titleWidth = 0;
	int titleHeight = 0;

	static const int options = 2;
	const char* labels[options] = {"Play Game","Exit"};
	int width = 800, height = 600, x, y;

	bool selected[options] = {true, false};

	int menuItems[4] = {0,0,0,0};

	SDL_Rect titleRect;

	SDL_Surface* menuItemOne;
	SDL_Texture* menuItemOneTexture;

	SDL_Surface* menuItemTwo;
	SDL_Texture* menuItemTwoTexture;

	SDL_Surface* menu[options];
	SDL_Texture* menuTexture[options];

	SDL_Rect rectPositionOne;
	SDL_Rect rectPositionTwo;


};
#endif
