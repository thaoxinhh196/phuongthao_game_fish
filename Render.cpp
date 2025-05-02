#include "Render.h"
SDL_Texture* rendertexture(SDL_Renderer* r, const std::string& text) {

    const char* fontpath = "assets/arial.ttf";

    TTF_Font* Font = TTF_OpenFont(fontpath, 24);
    if (!Font) std::cout << " font not load" << TTF_GetError() << std::endl;;
    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, text.c_str(), White);
    // now you can convert it into a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    return texture;

}