#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Fish.h"
#include "Render.h"


int main(int argc, char* argv[]) {
    SDL_Texture* textTexture = nullptr;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Window* window = SDL_CreateWindow("Ca lon nuot ca be", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* background = IMG_LoadTexture(renderer, "assets/background.png");
    SDL_Texture* fishTexture = IMG_LoadTexture(renderer, "assets/player.png");
    SDL_Texture* smallFishTexture = IMG_LoadTexture(renderer, "assets/small_fish.png");
    Mix_Chunk* eatSound = Mix_LoadWAV("assets/eat.wav");
    Uint32 lastspawntime = SDL_GetTicks();
    TTF_Init();
    Uint32 point = 0;
    srand(time(NULL));
    if (!background) {
        std::cerr << "Lỗi tải ảnh nền: " << IMG_GetError() << std::endl;
    }
    if (!fishTexture) {
        std::cerr << "Lỗi tải ảnh cá lớn: " << IMG_GetError() << std::endl;
    }
    if (!smallFishTexture) {
        std::cerr << "Lỗi tải ảnh cá nhỏ: " << IMG_GetError() << std::endl;
    }
    if (!eatSound) {
        std::cerr << "Lỗi tải âm thanh: " << Mix_GetError() << std::endl;
    }
    int fishFrameWidth = 125; // Chiều rộng của mỗi frame trong spritesheet
    SDL_Rect player = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, fishFrameWidth, 105 };
    std::vector<Fish> fishList;



    bool running = true;
    SDL_Event e;
    Uint32 lastUpdateTime = SDL_GetTicks();
    int prevMouseX = SCREEN_WIDTH / 2;
    SDL_RendererFlip flipState = SDL_FLIP_HORIZONTAL;
    std::stringstream ss;
    ss << "Point: " << point;
    std::string textpoint = ss.str();
    textTexture = rendertexture(renderer, textpoint);

    while (running) {
       

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastspawntime >= 5000 ) {
            
            for (int i = 0; i < 5; i++) {
                int x = rand() % (SCREEN_WIDTH - 50);
                int y = rand() % (SCREEN_HEIGHT - 50);
                fishList.emplace_back(smallFishTexture, x, y, 65, 48, 2, 2);
            }
            lastspawntime = currentTime;
        }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEMOTION) {
                player.x = e.motion.x - player.w / 2;
                player.y = e.motion.y - player.h / 2;

                if (e.motion.x > prevMouseX) {
                    flipState = SDL_FLIP_HORIZONTAL; 
                }
                else if (e.motion.x < prevMouseX) {
                    flipState = SDL_FLIP_NONE; 
                }
                prevMouseX = e.motion.x;
            }
        }

        for (auto& fish : fishList) {
            if (fish.alive && SDL_HasIntersection(&player, &fish.rect)) {
                fish.alive = false;
                Mix_PlayChannel(-1, eatSound, 0);
                point++;
                ss.str("");
                ss.clear();
                ss << "Point: " << point;
                std::string textpoint = ss.str();
                textTexture = rendertexture(renderer, textpoint);
                std::cout << point;
            }
            fish.updateAnimation(currentTime);
            fish.updateMovement();
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        int textW, textH;
        SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
        SDL_Rect dstRect = { 10, 10, textW, textH };
        SDL_RenderCopy(renderer, background, NULL, NULL);


        for (auto& fish : fishList) {
            fish.render(renderer, 65); 

        }
        int frameIndex = (SDL_GetTicks() / FRAME_DELAY) % 4; 

        int srcX = (frameIndex % 2) * fishFrameWidth;  
        int srcY = (frameIndex / 2) * 105;            

        SDL_Rect srcRect = { srcX, srcY, fishFrameWidth, 105 };
        SDL_RenderCopyEx(renderer, fishTexture, &srcRect, &player, 0, NULL, flipState);
        SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

        SDL_RenderPresent(renderer);
        //SDL_Delay(10);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(fishTexture);
    SDL_DestroyTexture(smallFishTexture);
    Mix_FreeChunk(eatSound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
