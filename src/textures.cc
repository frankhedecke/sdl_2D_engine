#include "textures.h"

void logError(const std::string &msg){
  std::cout << ">>> " << msg << " error" << std::endl;
}

void logSDLError(const std::string &msg){
  std::cout << ">>> " << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* ren){

  SDL_Texture *texture = IMG_LoadTexture(ren, path.c_str());

  if (texture == nullptr){
    logSDLError("LoadTexture");
  }
  return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip) {

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != nullptr) {
    dst.w = clip->w;
    dst.h = clip->h;
  } else {
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
  }

  SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h, SDL_Rect* clip) {

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;

  SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTextureCentered(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip) {

  SDL_Rect dst;
  if (clip != nullptr) {
    dst.w = clip->w;
    dst.h = clip->h;
  } else {
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
  }
  dst.x = x - dst.w / 2;
  dst.y = y - dst.h / 2;

  SDL_RenderCopy(ren, tex, clip, &dst);
}

SDL_Texture* renderText(const std::string &text, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer) {

  TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
  if (font == nullptr){
    logSDLError("TTF_OpenFont");
    return nullptr;
  }	

  SDL_Surface *text_surface = text_surface=TTF_RenderUTF8_Solid(font, text.data(), color);
  if (text_surface == nullptr){
    logSDLError("TTF_RenderUTF8_Solid");
    TTF_CloseFont(font);
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);
  if (texture == nullptr){
    logSDLError("CreateTextureFromSurface");
  }

  SDL_FreeSurface(text_surface);
  TTF_CloseFont(font);
  return texture;
}
