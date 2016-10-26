#pragma once

#include <string>
#include <SDL.h>

#include "animation.h"

#define uint uint16_t

class vector_screen {

  private:
    // fullscreen
    uint _fs_res_x;
    uint _fs_res_y;
    uint _fs_res;
    uint _fs_offset_x;
    uint _fs_offset_y;
    // window mode
    uint _res_x;
    uint _res_y;
    uint _res;
    uint _bup_res;
    uint _offset_x;
    uint _offset_y;
    // other
    SDL_Renderer* _renderer;
    SDL_Window* _window;
    bool _is_fullscreen;
    void param(uint res_x, uint res_y, uint* base_res, uint* offset_x, uint* offset_y);

  public:
    vector_screen(SDL_Window* window);
    ~vector_screen();
    void update_res();
    void toggle_fullscreen();
    Animation* load_Animation_Seq(const std::string &path, uint32_t count);
    SDL_Texture* load_Texture(const std::string &path);
    SDL_Texture* loadText(const std::string &text, int font_size);
    void render_Texture(float x, float y, float dim_x, float dim_y, SDL_Texture* tex);
    void render_Animation(float x, float y, float dim_x, float dim_y, Animation* animation);
    void present();
    void clear();
    SDL_Renderer* get_renderer();
    // TODO
    // rename methods with _
    // rename into Vector_screen
    // void renderTextureCentered(SDL_Texture* tex, float x, float y);
    // SDL_Texture* clipTexture(SDL_Texture* tex, int x, int y);
};
