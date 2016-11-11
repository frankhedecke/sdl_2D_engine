#include "scene.h"

Scene::Scene(Scene_Manager* manager) 
: _manager(manager) {

  _screen = _manager->get_vector_screen();
}

Scene::~Scene() {}
