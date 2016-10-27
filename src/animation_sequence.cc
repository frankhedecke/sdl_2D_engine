#include <SDL.h>
#include <SDL_image.h>

#include "animation_sequence.h"

Animation_Sequence::Animation_Sequence(vector_screen* screen, const std::string &path, uint32_t count) {

  _screen = screen;
  _count = count;
  // _texture = _screen->load_Texture(path);
  _cur_seq = 0;

  // generate textures
  SDL_Surface* sfc = IMG_Load(path.data());

  for (uint32_t i = 0; i < count; ++i) {

    SDL_Rect rect;
    rect.w = sfc->w / count;
    rect.h = sfc->h;
    rect.x = i * rect.w;
    rect.y = 0;

    SDL_Rect rect_dst;
    rect_dst.w = sfc->w / count;
    rect_dst.h = sfc->h;
    rect_dst.x = 0;
    rect_dst.y = 0;

    SDL_Surface* dst = SDL_CreateRGBSurface(0, rect.w, rect.h, sfc->format->BitsPerPixel, 
        sfc->format->Rmask, sfc->format->Gmask, sfc->format->Bmask, sfc->format->Amask);

    SDL_SetClipRect(sfc, &rect);

    SDL_BlitSurface(sfc, &rect, dst, &rect_dst);

    SDL_Texture* tex = SDL_CreateTextureFromSurface(_screen->get_renderer(), dst);

    _vec_tex.push_back(tex);

    SDL_FreeSurface(dst);
  }

  SDL_FreeSurface(sfc);
}

SDL_Texture* Animation_Sequence::get_cur_texture() {

  SDL_Texture* tex = _vec_tex.at(_cur_seq);

  _cur_seq ++;

  if (_cur_seq >= _count)
    _cur_seq = 0;

  return tex;
}
