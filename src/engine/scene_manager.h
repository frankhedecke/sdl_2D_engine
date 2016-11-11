#pragma once

#include "scene.h"
#include "vector_screen.h"

class Scene;

class Scene_Manager {

  private:
    vector_screen* _screen;
    Scene* _cur_scene;

  public:
    Scene_Manager(vector_screen* screen);
    ~Scene_Manager();
    void load_scene(Scene* scene);
    // TODO const pointer
    vector_screen* get_vector_screen();
    void tick(bool &quit);

    // TODO
    // int pause_cur_scene();
    // void continue_sceen(int scene_id);
};
