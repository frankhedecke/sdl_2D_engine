#include "scene_manager.h"

Scene_Manager::Scene_Manager(vector_screen* screen)
: _screen(screen) {

  _cur_scene = nullptr;
}

Scene_Manager::~Scene_Manager() {

  _screen->~vector_screen();
  _cur_scene->~Scene();
}

void Scene_Manager::load_scene(Scene* scene) {
  
  // delete or pause current scene

  // load new scene
  _cur_scene = scene;
}

vector_screen* Scene_Manager::get_vector_screen() {

  return _screen;
}

void Scene_Manager::tick(bool &quit) {
  
  if (_cur_scene != nullptr)
    _cur_scene->tick(quit);
}
