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

    Draw_Object();
    ~Draw_Object();
    virtual void left_click() = 0;
    virtual void right_click() = 0;
    virtual void mouse_over() = 0;
    bool covers(float x, float y);
};
