#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#ifndef RENDER_H
#define RENDER_H
SDL_Texture* rendertexture(SDL_Renderer* r, const std::string& text);
#endif
