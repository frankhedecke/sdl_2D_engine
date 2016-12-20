#include "object_scene.h"

Object_Scene::Object_Scene(Scene_Manager* manager)
: Scene(manager) {}

Object_Scene::~Object_Scene() {}

void Object_Scene::tick(bool &quit) {

  pre_tick(quit);

  for (Draw_Object* obj : _draw_objects) {
    _screen->render_Texture(obj->_x, obj->_y, obj->_dim_x, obj->_dim_y, obj->_tex);
  }

  post_tick(quit);


}

#include <SDL.h>
void Object_Scene::add_object(Draw_Object* object) {

  // TODO decide if drawable and/or mouse sensitive
  _draw_objects.push_front(object);
  _mouse_objects.push_front(object);
}

void Object_Scene::left_click(float x, float y) {

  for (Draw_Object* obj : _draw_objects) {
    if (obj->covers(x, y)) {
      obj->left_click();
      return;
    }
  }
}

void Object_Scene::mouse_over(float x, float y) {

  for (Draw_Object* obj : _draw_objects) {
    if (obj->covers(x, y)) {
      obj->mouse_over();
      return;
    }
  }
}
