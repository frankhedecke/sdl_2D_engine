#include <SDL.h>

#include "animation_sequence.h"

Animation_Sequence::Animation_Sequence(vector_screen* screen, const std::string &path, uint32_t count) {

  _screen = screen;
  _count = count;
  _texture = _screen->load_Texture(path);
}

SDL_Texture* Animation_Sequence::get_cur_texture() {

  // TODO change this
  return _texture;
}
