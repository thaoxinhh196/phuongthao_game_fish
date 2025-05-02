

#ifndef FISH_H
#define FISH_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_surface.h>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FRAME_COUNT = 4;
const int FRAME_DELAY = 100;

class Fish {
public:
    SDL_Texture* texture;
    SDL_Rect rect;
    bool alive = true;
    int frame = 0;
    Uint32 lastFrameTime = 0;
    int col = 0;
    int row = 0;
    int speed;
    int direction;
    SDL_RendererFlip flipState = SDL_FLIP_HORIZONTAL;

    Fish(SDL_Texture* tex, int x, int y, int w, int h, int c, int r);

    void render(SDL_Renderer* renderer, int frameWidth);
    void updateAnimation(Uint32 currentTime);
    void swim(SDL_Renderer* renderer, int x, int y);
    void swimRandom(SDL_Renderer* renderer);
    void updateMovement();
};

#endif

