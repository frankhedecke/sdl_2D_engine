#pragma once
#include <vector>
#include <SDL.h>

#include "scene.h"
#include "scene_manager.h"

class Scene_Intro : public Scene {

  private:
    uint32_t _startup_ticks;
    int16_t _x_pos;
    int16_t _y_pos;
    uint32_t _gen_counter;
    std::vector<std::vector<SDL_Texture*>> _cache;
    int16_t _x_cache_window;
    int16_t _y_cache_window;
    int16_t _x_cache_radius;
    int16_t _y_cache_radius;
    int16_t _x_cache_pos;
    int16_t _y_cache_pos;
    int16_t _x_cache_value;
    int16_t _y_cache_value;
    void* _ring1[13];
    int32_t _ring1_cur;
    SDL_Texture* _tex_name;
    // FULLSCREEN
    bool _keys[5];

    void input(SDL_Event* event);
    void process();
    void output();
    SDL_Texture* init_cache_array(int16_t x, int16_t y);
    SDL_Texture* init_cache_vector(int16_t x, int16_t y);
    SDL_Texture* get_cached(int16_t x, int16_t y);
    SDL_Texture* generate_tile(int16_t x, int16_t y, uint32_t seed, uint32_t star_count);

  public:
    Scene_Intro(Scene_Manager* manager);
    ~Scene_Intro();
    void tick(bool &quit);
};
