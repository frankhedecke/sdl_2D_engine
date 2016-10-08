#pragma once

#include <SDL.h>

#include "scene.h"
#include "scene_manager.h"

class Scene_Intro : public Scene {

  private:
    uint32_t _startup_ticks;
    int16_t _x_pos;
    int16_t _y_pos;
    void* _ring1[13];
    int32_t _ring1_cur;
    SDL_Texture* _tex_name;
    // FULLSCREEN
    bool _keys[5];

    void input(SDL_Event* event);
    void process();
    void output();
    void* ring_alloc(int pos);
    SDL_Texture* get_tile(int x, int y, uint32_t seed, uint32_t star_count);

  public:
    Scene_Intro(Scene_Manager* manager);
    ~Scene_Intro();
    void tick(bool &quit);
};
