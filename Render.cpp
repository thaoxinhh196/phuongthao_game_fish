#include "Render.h"
SDL_Texture* rendertexture(SDL_Renderer* r, const std::string& text) {

    const char* fontpath = "assets/arial.ttf";

    TTF_Font* Font = TTF_OpenFont(fontpath, 24);
    if (!Font) std::cout << " font not load" << TTF_GetError() << std::endl;;
    SDL_Color White = { 255, 255, 255 };//mau trang
    
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, text.c_str(), White);
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    return texture;

}
