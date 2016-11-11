#pragma once

#include "scene_manager.h"
#include "vector_screen.h"

class Scene_Manager;

class Scene {

  protected:
    vector_screen* _screen;
    Scene_Manager* _manager;

  public:
    Scene(Scene_Manager* manager);
    ~Scene();
    virtual void tick(bool &quit) = 0;
};
