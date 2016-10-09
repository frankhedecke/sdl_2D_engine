// TODO stop the segfaulting

#include <iostream> // TODO remove
#include <random>
#include "scene_intro.h"

void* Scene_Intro::ring_alloc(int pos) {
  // TODO do some deep thinking about ring_buffers, that uses arrays
  if ((_ring1_cur + 6 - pos) < 0) {
  }
}

// tile is 64x64
SDL_Texture* Scene_Intro::get_tile(int16_t x, int16_t y, uint32_t seed = 0, uint32_t star_count = 5) {

//  std::cout << "create tile at " << x << "." << y << std::endl;

  SDL_Surface* surface = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0);
  if (surface == nullptr)
    std::cout << "surface is NULL" << std::endl;

  uint32_t* pixels = (uint32_t*) surface->pixels;



  std::mt19937 generator (seed + (uint16_t) x + 97 * (uint16_t) y);
  std::uniform_int_distribution<int> distribution(1,64);

  for (int i = 0; i < star_count; ++i) {
    int star_x = distribution(generator);
    int star_y = distribution(generator);
    //std::cout << star_x << "." << star_y << std::endl;
    *(pixels + 64 * star_x + star_y) = 0xff0000;
  }

  SDL_Texture* tex = SDL_CreateTextureFromSurface(_screen->get_renderer(), surface);

  if (surface != nullptr)
    SDL_FreeSurface(surface);

  return tex;
}

void Scene_Intro::input(SDL_Event* event) {

  if (event->type == SDL_KEYDOWN) {
    switch(event->key.keysym.sym) {
      case SDLK_w:    _keys[0] = true; break;
      case SDLK_s:    _keys[1] = true; break;
      case SDLK_a:    _keys[2] = true; break;
      case SDLK_d:    _keys[3] = true; break;
    }
  } else if (event->type == SDL_KEYUP) {
    // TODO check if buttons are pressed or already are released
    switch(event->key.keysym.sym) {
      case SDLK_w:    _keys[0] = false; break;
      case SDLK_s:    _keys[1] = false; break;
      case SDLK_a:    _keys[2] = false; break;
      case SDLK_d:    _keys[3] = false; break;
    }
  }
}

void Scene_Intro::process() {

  // clear screen
  _screen->clear();

  // update position
  if (_keys[0])
    _y_pos += 2;
  if (_keys[1])
    _y_pos -= 2;
  if (_keys[2])
    _x_pos += 2;
  if (_keys[3])
    _x_pos -= 2;

  // std::cout << _x_pos << " : " << _y_pos << std::endl;

  int16_t tile_x = _x_pos / 10;
  int16_t tile_y = _y_pos / 10;
  // TODO add 10th offset with modulo somewhere

  // std::cout << "tile " << tile_x << " : " << tile_y << std::endl;

  // render background
  for (int x = 0; x < 10; ++x)
    for (int y = 0; y < 8; ++y) {
      SDL_Texture* tile = get_tile(x + tile_x, y + tile_y);
      if (tile == nullptr)
        std::cout << "tile is NULL" << std::endl;
      else {
        _screen->render_Texture(0.1 * x, 0.1 * y, 0.1, 0.1, tile);
        SDL_DestroyTexture(tile);
      }
    }

  // render text
  _screen->render_Texture(0.2, 0.1, 0.6, 0.1,  _tex_name);
}

void Scene_Intro::output() {

  _screen->present();
  SDL_Delay(50);
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
