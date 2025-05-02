#include "Fish.h"

Fish::Fish(SDL_Texture* tex, int x, int y, int w, int h, int c, int r) {
    texture = tex;
    rect = { x, y, w, h };
    col = c;
    row = r;
    speed = 2 + rand() % 3;
    direction = (rand() % 2) ? 1 : -1;
    flipState = (direction == 1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void Fish::render(SDL_Renderer* renderer, int frameWidth) {
    if (alive) {
        int frameIndex = (SDL_GetTicks() / FRAME_DELAY) % (col * row);
        int srcX = (frameIndex % col) * frameWidth;
        int srcY = (frameIndex / col) * frameWidth;

        SDL_Rect srcRect = { srcX, srcY, frameWidth, rect.h };
        SDL_RenderCopyEx(renderer, texture, &srcRect, &rect, 0, NULL, flipState);
    }
}

void Fish::updateAnimation(Uint32 currentTime) {
    if (currentTime > lastFrameTime + FRAME_DELAY) {
        frame = (frame + 1) % FRAME_COUNT;
        lastFrameTime = currentTime;
    }
}

void Fish::swim(SDL_Renderer* renderer, int x, int y) {
    rect.x = x;
    rect.y = y;
    render(renderer, rect.w);
}

void Fish::swimRandom(SDL_Renderer* renderer) {
    srand(time(NULL));
    int randomFlip = rand() % 2;
    while (alive) {
        if (randomFlip == 1) {
            flipState = SDL_FLIP_NONE;
            rect.x -= 1;
        }
        else {
            rect.x += 1;
            flipState = SDL_FLIP_HORIZONTAL;
        }
        render(renderer, rect.w);
    }
}

void Fish::updateMovement() {
    rect.x += speed * direction;
    if (rect.x < -rect.w || rect.x > SCREEN_WIDTH) {
        rect.x = (direction == 1) ? -rect.w : SCREEN_WIDTH;
        rect.y = rand() % (SCREEN_HEIGHT - rect.h);
        speed = 2 + rand() % 3;
        direction = (rand() % 2) ? 1 : -1;
        flipState = (direction == 1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    }
}
