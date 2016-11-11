#pragma once

#include <vector>
#include <SDL.h>

#include "animation.h"
#include "vector_screen.h"

class Animation_Sequence : Animation {

  private:
    uint32_t _cur_seq;
    SDL_Texture* _texture; // TODO remove
    uint32_t _count;
    vector_screen* _screen;
    std::vector<SDL_Texture*> _vec_tex;

  public:
    // TODO rename count
    Animation_Sequence(vector_screen* screen, const std::string &path, uint32_t count);
    SDL_Texture* get_cur_texture();
};

// write destructor that frees the textures
