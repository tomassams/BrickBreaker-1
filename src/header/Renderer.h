//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_RENDERER_H
#define BRICKBREAKER_RENDERER_H

#include <SDL.h>
#include "Bricks.h"


class Renderer {
public:
    void initialize();
    void destroy();
    void drawPaddle(SDL_Rect rect);
    void drawBall(SDL_Rect rect);
    void drawBrick(SDL_Rect rect);
    void drawBricks(Bricks &bricks);
    SDL_Renderer* getRenderer();
private:
    int WIDTH = 800, HEIGHT = 600;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Surface *ballSurface;
    SDL_Texture *ballTexture;

    SDL_Surface *paddleSurface;
    SDL_Texture *paddleTexture;

    SDL_Surface *brickSurface;
    SDL_Texture *brickTexture;
};



#endif //BRICKBREAKER_RENDERER_H
