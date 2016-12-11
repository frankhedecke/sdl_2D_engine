#pragma once
#include <SDL.h>
// TODO make this struct solely pixel based


class Draw_Object {

  public:
    float _x;
    float _y;
    float _dim_x;
    float _dim_y;
    SDL_Texture* _tex;

    virtual void left_click();
    bool covers(float x, float y);
};
