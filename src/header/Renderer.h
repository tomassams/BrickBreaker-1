//
// Created by ts on 4/24/2019.
//

#ifndef BRICKBREAKER_RENDERER_H
#define BRICKBREAKER_RENDERER_H

#include <SDL.h>


class Renderer {
public:
    void initialize();
    void destroy();
    void draw();
    void drawPaddle(SDL_Rect rect);
    void drawBall(SDL_Rect rect);
    SDL_Renderer* getRenderer();
private:
    int WIDTH = 800, HEIGHT = 600;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Surface *ballSurface;
    SDL_Texture *ballTexture;
    SDL_Rect ballRect;

    SDL_Surface *paddleSurface;
    SDL_Texture *paddleTexture;
    SDL_Rect paddleRect;
};



#endif //BRICKBREAKER_RENDERER_H
