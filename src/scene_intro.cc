#include <iostream> // TODO remove
#include <random>
#include <vector>
#include "scene_intro.h"

SDL_Texture* Scene_Intro::init_cache_array(int16_t x, int16_t y) {
  return nullptr;
}

SDL_Texture* Scene_Intro::init_cache_vector(int16_t x, int16_t y) {

  std::cout << "destroy old cache ..." << std::endl;
  for (uint16_t i=0; i < _cache.size(); ++i) {
    for (uint16_t j=0; j < _cache.at(i).size(); ++j) {
      SDL_DestroyTexture(_cache.at(i).at(j));
    }
    _cache.at(i).clear();
  }
  _cache.clear();
  std::cout << "old cache is destroyed" << std::endl;

  int xii = 0;

  for (int16_t xi = x - _x_cache_radius; xi <= _x_cache_window + _x_cache_radius; ++xi) {

    std::vector<SDL_Texture*> column;

    _cache.push_back(column);

    for (int16_t yi = y - _y_cache_radius; yi <= _y_cache_window + _y_cache_radius; ++yi) {
      std::cout << "cache " << std::endl;
      _cache.at(xii).push_back(generate_tile(xi, yi, 0 ,5));

      //column.push_back(generate_tile(xi, yi, 0 ,5));
    }
    ++xii;
  }

  _x_cache_pos = 0;
  _y_cache_pos = 0;
  _x_cache_value = x - _x_cache_radius;
  _y_cache_value = y - _y_cache_radius;

  std::cout << "INIT: cache is new for " << x << "." << y << std::endl;
  std::cout << "INIT: POS = " << _x_cache_pos << "." << _y_cache_pos << std::endl;
  std::cout << "INIT: VAL = " << _x_cache_value << "." << _y_cache_value << std::endl;


  for (unsigned i=0; i<_cache.size(); i++)
    std::cout << _cache.at(i).size() << std::endl;

  return _cache.at(_x_cache_radius).at(_y_cache_radius);
}

SDL_Texture* Scene_Intro::get_cached(int16_t x, int16_t y) {
  //std::cout << "is " << x << "." << y << " cached?" << std::endl;
  // TODO do some deep thinking about ring_buffers, that uses arrays
  // TODO write a cache with 2D array on the heap

  int16_t x_min = _x_cache_value;
  int16_t x_max = _x_cache_value + 2 * _x_cache_radius + _x_cache_window;
  int16_t y_min = _y_cache_value;
  int16_t y_max = _y_cache_value + 2 * _y_cache_radius + _y_cache_window;

  if ((x_min <= x) && (x <= x_max)) {
    //std::cout << "inside x-cache, from " << x_min << " to " << x_max << std::endl;
    if ((y_min <= y) && (y <= y_max)) {
      //std::cout << "inside y-cache, from " << y_min << " to " << y_max << std::endl;
      // tile inside cache
//      return _cache.at(x - _x_cache_value).at(y - _y_cache_value);
      // TODO rework, because this will only works if cache positions are 0,0
      if ((_x_cache_pos == 0) && (_y_cache_pos == 0)) {
        //std::cout << "cached in " << x - _x_cache_value << "." << y - _y_cache_value << std::endl;
        return _cache.at(x - _x_cache_value).at(y - _y_cache_value);
      }
      else
        return generate_tile(x, y, 0 ,5);
    }
  }

  // generate all the cache

  return init_cache_vector(x, y);
}

// tile is 64x64
SDL_Texture* Scene_Intro::generate_tile(int16_t x, int16_t y, uint32_t seed = 0, uint32_t star_count = 5) {

  ++_gen_counter;
  std::cout << "create tile " << _gen_counter << " at " << x << "." << y << std::endl;

  SDL_Surface* surface = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0);
  if (surface == nullptr)
    std::cout << "surface is NULL" << std::endl;

  if ( SDL_LockSurface(surface) != 0 )
    return nullptr;

  uint32_t* pixels = (uint32_t*) surface->pixels;
  //std::cout << pixels << std::endl;

  std::mt19937 generator (seed + (uint16_t) x + 97 * (uint16_t) y);
  std::uniform_int_distribution<int> distribution(0, 63);

  for (int i = 0; i < star_count; ++i) {
    uint32_t star_x = distribution(generator);
    uint32_t star_y = distribution(generator);
    //std::cout << star_x << "." << star_y << std::endl;
    *(pixels + 64 * star_x + star_y) = 0x00ffffff;
  }

  SDL_UnlockSurface(surface);
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
    _y_pos -= 2;
  if (_keys[1])
    _y_pos += 2;
  if (_keys[2])
    _x_pos -= 2;
  if (_keys[3])
    _x_pos += 2;

  // std::cout << _x_pos << " : " << _y_pos << std::endl;

  int16_t tile_x = _x_pos / 10;
  int16_t tile_y = _y_pos / 10;  
  int16_t offset_x = _x_pos % 10;
  int16_t offset_y = _y_pos % 10;

  // render background
  for (int x = -2; x < 10; ++x)
    for (int y = -2; y < 8; ++y) {
      SDL_Texture* tile = get_cached(x + tile_x, y + tile_y);
      if (tile == nullptr)
        std::cout << "tile is NULL" << std::endl;
      else {
        _screen->render_Texture((0.1 * x) + ((float) (10 - offset_x) / 100), 0.1 * y + ((float) (10 - offset_y) / 100), 0.1, 0.1, tile);
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

  _gen_counter = 0;
  _tex_name = _screen->loadText("a game made with SDL", 48);
  _startup_ticks = SDL_GetTicks();
  _x_pos = 0;
  _y_pos = 0;
  _x_cache_window = 12;
  _y_cache_window = 10;
  _x_cache_radius = 3;
  _y_cache_radius = 3;
  for (int i = 0; i < 5; ++i)
    _keys[i] = false;
  // ring buffer
  _ring1_cur = 15;
  init_cache_vector(_x_pos / 10, _y_pos / 10);
}

Scene_Intro::~Scene_Intro() {}
