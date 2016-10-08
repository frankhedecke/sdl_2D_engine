#include "textures.h"
#include "vector_screen.h"

// TODO problem: ratio 4 : 3 is hardcoded
vector_screen::vector_screen(SDL_Window* window) : _window(window) {

  // calculate fullscreen parameters
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  _fs_res_x = mode.w;
  _fs_res_y = mode.h;
  _fs_res = 0;
  _fs_offset_x = 0;
  _fs_offset_y = 0;
  param(_fs_res_x, _fs_res_y, &_fs_res, &_fs_offset_x, &_fs_offset_y);

  // calculate window parameters
  update_res(); 
  _bup_res = _res_x;

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // TODO check if window is fullscreen
  _is_fullscreen = false;
}

vector_screen::~vector_screen() {

  SDL_DestroyRenderer(_renderer);
}

void vector_screen::param(uint res_x, uint res_y, uint* base_res, uint* offset_x, uint* offset_y) {

  if ( (res_x * 3) == (res_y * 4) ) {
    *base_res = res_x;
  } else if ( (res_x * 3) > (res_y * 4) ) {
    *base_res = res_y * 4 / 3;
    *offset_x = (res_x - *base_res) / 2;
  } else {
    *base_res = res_x;
    *offset_y = (res_y - res_x * 3 / 4) / 2 ;
  }
}

void vector_screen::update_res() {
  // window resoultions change if fullscreen is entered
  // but are restored if fullscreen is left
  int w, h = 0;
  SDL_GetWindowSize(_window, &w, &h);
  _res_x = w;
  _res_y = h;
  _res = 0;
  _offset_x = 0;
  _offset_y = 0;

  param(_res_x, _res_y, &_res, &_offset_x, &_offset_y);
}

void vector_screen::toggle_fullscreen() {

  Uint32 win_flags = 0;

  if (_is_fullscreen) {
    _is_fullscreen = false;
    // restore window resolution
    _res = _bup_res;
    // set to window mode
    SDL_SetWindowFullscreen(_window, win_flags);
    SDL_SetWindowSize(_window, _res, _res / 4 * 3);
    SDL_RenderSetScale(_renderer, 1.0, 1.0);
  } else {
    _is_fullscreen = true;
    // backup window resolution
    int w = 0;
    SDL_GetWindowSize(_window, &w, nullptr);
    _bup_res = w;
    // set to fullscreen mode
    win_flags = SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowSize(_window, _fs_res_x, _fs_res_y);
    SDL_SetWindowFullscreen(_window, win_flags);
    SDL_RenderSetScale(_renderer, 1.0, 1.0);
  }
}

SDL_Texture* vector_screen::load_Texture(const std::string &path) {

  return loadTexture(path, _renderer);
}

SDL_Texture* vector_screen::loadText(const std::string &text, int font_size) {

  // white text is standard
  SDL_Color color = {255, 255, 255, 255};
  return renderText(text, "fonts/font.ttf", color, font_size, _renderer);
}

void vector_screen::render_Texture(float x, float y, float dim_x, float dim_y, SDL_Texture* tex) {

  int res = 0;
  int off_x = 0;
  int off_y = 0;

  if (_is_fullscreen) {
    res = _fs_res;
    off_x = _fs_offset_x;
    off_y = _fs_offset_y;
  } else {
    res = _res;
    off_x = _offset_x;
    off_y = _offset_y;
  }

  int pix_x = x * res + off_x;
  int pix_y = y * res + off_y;
  int pix_w = dim_x * res;
  int pix_h = dim_y * res;

  renderTexture(tex, _renderer, pix_x, pix_y, pix_w, pix_h, nullptr);
}

void vector_screen::present() {

  SDL_RenderPresent(_renderer);
}

void vector_screen::clear() {
  SDL_RenderClear(_renderer);
}


SDL_Renderer* vector_screen::get_renderer() {
  // TODO remove this method
  return _renderer;
}
