#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <scene_manager.h>
#include <vector_screen.h>
#include "scene_map.h"

const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT =  768;

using namespace std;

int init_main(SDL_Window* &window, vector_screen* &screen) {

  // init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (TTF_Init() != 0){
    std::cout << "TTF_Init error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // TODO move window creation to vector screen
  int win_flags = SDL_WINDOW_SHOWN + SDL_WINDOW_RESIZABLE;
  window = SDL_CreateWindow("SDL Pong - press ESCAPE to exit", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);

  if (window == nullptr) {
    std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  screen = new vector_screen(window);


  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  return 0;
}

int main(int argc, char** argv) {

  SDL_Window *window = nullptr;
  vector_screen *screen = nullptr;
  Scene_Manager *manager = nullptr;
  Scene_Map *scene_map = nullptr;

  init_main(window, screen);

  // TODO move vector screen creation to scene_manager
  manager = new Scene_Manager(screen);
  scene_map = new Scene_Map(manager);
  manager->load_scene(scene_map);

  bool quit = false;

  while (!quit) {
    manager->tick(quit);
  }

  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
