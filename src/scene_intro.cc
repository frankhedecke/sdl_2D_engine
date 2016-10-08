#include "scene_intro.h"

void Scene_Intro::input(SDL_Event* event) {}

void Scene_Intro::process() {

  // clear screen
  _screen->clear();

  // render text
  _screen->render_Texture(0.2, 0.1, 0.6, 0.1,  _tex_name);
}

void Scene_Intro::output() {

  _screen->present();
}


void Scene_Intro::tick(bool &quit) {

  SDL_Event e;
  
  // loop will be entered if an event occurrs
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
             quit = true; break;
        case SDLK_f:
             _keys[4] = true; break;
      }
    } else if (e.type == SDL_KEYUP) {
      if (e.key.keysym.sym == SDLK_f && _keys[4]) {
         _keys[4] = false;
         _screen->toggle_fullscreen(); 
      }

    } else if (e.type == SDL_WINDOWEVENT) {
       if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
         _screen->update_res();
       }
    }

    input(&e);
  }

  process();
  output();
}

Scene_Intro::Scene_Intro(Scene_Manager* manager) : Scene(manager) {

  _tex_name = _screen->loadText("a game made with SDL", 48);
  _startup_ticks = SDL_GetTicks();
  for (int i = 0; i < 5; ++i)
    _keys[i] = false;
}

Scene_Intro::~Scene_Intro() {}
