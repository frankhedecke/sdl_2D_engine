#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

void logError(const std::string &msg);

void logSDLError(const std::string &msg);

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* ren);

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr);

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h, SDL_Rect* clip = nullptr);

void renderTextureCentered(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr);

SDL_Texture* renderText(const std::string &text, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);
