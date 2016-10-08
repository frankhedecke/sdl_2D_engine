#include <iostream> // TODO remove
#include <random>
#include "scene_intro.h"

void* Scene_Intro::ring_alloc(int pos) {
  // TODO do some deep thinking about ring_buffers, that uses arrays
  if ((_ring1_cur + 6 - pos) < 0) {
  }
}

// tile is 64x64
SDL_Texture* Scene_Intro::get_tile(int x, int y, uint32_t seed = 0, uint32_t star_count = 5) {

  std::cout << "create tile at " << x << "." << y << std::endl;

  SDL_Surface* surface = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0);
  uint32_t* pixels = (uint32_t*) surface->pixels;



  std::mt19937 generator (seed + x + 97 * y);
  std::uniform_int_distribution<int> distribution(1,64);

  for (int i = 0; i < star_count; ++i) {
    int star_x = distribution(generator);
    int star_y = distribution(generator);
    std::cout << star_x << "." << star_y << std::endl;
    *(pixels + 64 * star_x + star_y) = 0xff0000;
  }




  // SDL_Texture* tex2 = SDL_CreateTexture(_screen->get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 64);
  SDL_Texture* tex = SDL_CreateTextureFromSurface(_screen->get_renderer(), surface);

  return tex;
}

void Scene_Intro::input(SDL_Event* event) {}

void Scene_Intro::process() {

  // clear screen
  _screen->clear();

  //void render_Texture(float x, float y, float dim_x, float dim_y, SDL_Texture* tex);

  // render background
  for (int x = 0; x < 10; ++x)
    for (int y = 0; y < 8; ++y)
      _screen->render_Texture(0.1 * x, 0.1 * y, 0.1, 0.1, get_tile(x, y));


  // render text
  _screen->render_Texture(0.2, 0.1, 0.6, 0.1,  _tex_name);
}

void Scene_Intro::output() {

  _screen->present();
  SDL_Delay(100);
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
  _x_pos = 0;
  _y_pos = 0;
  for (int i = 0; i < 5; ++i)
    _keys[i] = false;
  // ring buffer
  _ring1_cur = 15;
  ring_alloc(0);
}

Scene_Intro::~Scene_Intro() {}
