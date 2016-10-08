#pragma once

#include <SDL.h>

#include "scene.h"
#include "scene_manager.h"

class Scene_Intro : public Scene {

  private:
    uint32_t _startup_ticks;
    SDL_Texture* _tex_name;
    // FULLSCREEN
    bool _keys[5];

    void input(SDL_Event* event);
    void process();
    void output();

  public:
    Scene_Intro(Scene_Manager* manager);
    ~Scene_Intro();
    void tick(bool &quit);
};
