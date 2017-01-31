#include "object_scene.h"

Object_Scene::Object_Scene(Scene_Manager* manager)
: Scene(manager) {

  int _mouse_x = -1;
  int _mouse_y = -1;
}

Object_Scene::~Object_Scene() {}

void Object_Scene::tick(bool &quit) {

  // consume mouse input and delegate keyboard input to input();
  handle_delegate_input(quit);

  // TODO rename pre_tick
  pre_tick(quit);

  _screen->clear();

  pre_draw();

  for (Draw_Object* obj : _draw_objects) {
    _screen->render_Texture(obj->_x, obj->_y, obj->_dim_x, obj->_dim_y, obj->_tex);
  }

  post_draw();

  _screen->present();
  SDL_Delay(50);
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

void Object_Scene::right_click(float x, float y) {

  for (Draw_Object* obj : _draw_objects) {
    if (obj->covers(x, y)) {
      obj->right_click();
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

void Object_Scene::handle_delegate_input(bool &quit) {

  // TODO maybe delete these bools
  bool click_left  = false;
  bool click_right = false;
  // update mouse positions
  SDL_GetMouseState(&_mouse_pos_x, &_mouse_pos_y);

  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_WINDOWEVENT) {

       if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
         _screen->update_res();
       }

    } else if (e.type == SDL_MOUSEBUTTONDOWN) {

      if ((SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(NULL, NULL))) {
        //std::cout << "SDL_MOUSEBUTTONDOWN LEFT" << std::endl;
        click_left = true;
      }
      if ((SDL_BUTTON(SDL_BUTTON_RIGHT) & SDL_GetMouseState(NULL, NULL))){
        //std::cout << "SDL_MOUSEBUTTONDOWN RIGHT" << std::endl;
        click_right = true;
      }

    } else if (e.type == SDL_KEYDOWN) {

      if(e.key.keysym.sym == SDLK_ESCAPE)
        quit = true;
      else
        input(&e);

    }

    // I use this for SDL_KEYUP and maybe other things
    input(&e);
  }

  uint res = _screen->get_cur_base_res();
  uint offset_x = _screen->get_cur_offset_x();
  uint offset_y = _screen->get_cur_offset_y();
  float mouse_x = 1.0 * (_mouse_pos_x - offset_x)/ res;
  float mouse_y = 1.0 * (_mouse_pos_y - offset_y)/ res;

  mouse_over(mouse_x, mouse_y);

  if (click_left) {
    left_click(mouse_x, mouse_y);
  }

  if (click_right) {
    right_click(mouse_x, mouse_y);
  }
}
