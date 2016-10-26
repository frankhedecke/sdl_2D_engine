#pragma once

#include <SDL.h>

#include "animation.h"
#include "vector_screen.h"

class Animation_Sequence : Animation {

  private:
    SDL_Texture* _texture;
    uint32_t _count;
    vector_screen* _screen;

  public:
    // TODO rename count
    Animation_Sequence(vector_screen* screen, const std::string &path, uint32_t count);
    SDL_Texture* get_cur_texture();
};

// write destructor that frees the texture
