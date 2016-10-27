#pragma once

#include <SDL.h>

class Animation {

  public:
    virtual SDL_Texture* get_cur_texture() = 0;
};
