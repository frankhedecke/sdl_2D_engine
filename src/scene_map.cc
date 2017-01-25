#include <iostream> // TODO remove
#include <random>
#include <vector>

#include "scene_map.h"
#include <SDL.h>

void Node::Node_Draw_Object::left_click() {

  std::cout << "node at float-pos " << _x << " / " << _y << " is left clicked." << std::endl;
}

void Node::Node_Draw_Object::right_click() {

  std::cout << "node at float-pos " << _x << " / " << _y << " is right clicked." << std::endl;
}

void Node::Node_Draw_Object::mouse_over() {

  std::cout << "node at float-pos " << _x << " / " << _y << " is hovered." << std::endl;
}

Node::Node(uint16_t x, uint16_t y, SDL_Texture* tex) : _pos_x(x), _pos_y(y) {

  _obj._x = 0.1 + 0.05 * _pos_x;
  _obj._y = 0.1 + 0.05 * _pos_y;
  _obj._dim_x = 0.02;
  _obj._dim_y = 0.02;
  _obj._tex = tex;

  _fill = 0;
  _diff_value = 0;
}

void Node::update() {

  _fill += _diff_value;
  _diff_value = 0;
}

Link::Link(Node* origin1, Node* origin2) : _origin1(origin1), _origin2(origin2) {

  _resistance = 100;
}

void Link::update() {

  float diff = _origin1->_fill - _origin2->_fill;
  _origin1->_diff_value -= diff / _resistance;
  _origin2->_diff_value += diff / _resistance;
}


void Scene_Map::input(SDL_Event* event) {

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

  // TODO move to class Scene
  // get mouse position
  uint32_t clicked = SDL_GetMouseState(&_mouse_x, &_mouse_y);
  _click_left  = SDL_BUTTON(SDL_BUTTON_LEFT)  & clicked;
  _click_right = SDL_BUTTON(SDL_BUTTON_RIGHT) & clicked;
}

void Scene_Map::process() {

  // update
  ++_mod_ticks;

  if (_mod_ticks >= 1) {
  
    _mod_ticks = 0;
    std::cout << "tick " << SDL_GetTicks() << std::endl;
    std::cout << "mouse at " << _mouse_x << "." << _mouse_y << std::endl;
    // TODO subtract the borders
    uint res = _screen->get_cur_base_res();
    uint offset_x = _screen->get_cur_offset_x();
    uint offset_y = _screen->get_cur_offset_y();
    //std::cout << "res " << res << std::endl;
    float mouse_x = 1.0 * (_mouse_x - offset_x)/ res;
    float mouse_y = 1.0 * (_mouse_y - offset_y)/ res;
    std::cout << "mouse at " << mouse_x << "|" << mouse_y << std::endl;
    std::cout << "offsets " << offset_x << "|" << offset_y << std::endl;
    mouse_over(mouse_x, mouse_y);

    if (_click_left) {
      left_click(mouse_x, mouse_y);
    }
    if (_click_right) {
      right_click(mouse_x, mouse_y);
    }

    // update all links
    for (Link* link : _links) link->update();

    // update all nodes
    for (Node* node : _nodes) node->update();

    // print nodes
    //for (Node* node : _nodes)
    //  std::cout << "node at " << node << " and at pos " << node->_pos_x << "." << node->_pos_y << " has " << node->_fill << " units" << std::endl;
  }
}

void Scene_Map::pre_tick(bool &quit) {

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
}

void Scene_Map::pre_draw() {
  // TODO move render background to non click list
  _screen->render_Texture(0, 0, 1.0, 0.75, _tex_bg);
}

void Scene_Map::post_draw() {}

Scene_Map::Scene_Map(Scene_Manager* manager) 
: Object_Scene(manager), Scene(manager) {

  _tex_bg = _screen->load_Texture("res/map.jpg");
  _tex_square = _screen->load_Texture("res/square.png");
  _startup_ticks = SDL_GetTicks();
  _mod_ticks = 0;
  for (int i = 0; i < 5; ++i)
    _keys[i] = false;
  // TODO move to class Scene or mouse Scene or Object scene
  int _mouse_x = -1;
  int _mouse_y = -1;
  bool _click_left = false;
  bool _click_right = false;

  // create nodes
  Node* n1 = new Node(1, 3, _tex_square);
  Node* n2 = new Node(4, 4, _tex_square);
  Node* n3 = new Node(5, 5, _tex_square);

  add_object(& n1->_obj);
  add_object(& n2->_obj);
  add_object(& n3->_obj);

  n1->_fill = 100;
  n2->_fill = 0;
  n3->_fill = 0;

  _nodes.push_front(n1);
  _nodes.push_front(n2);
  _nodes.push_front(n3);

  // create links
  Link* l1_2 = new Link(n1, n2);
  Link* l2_3 = new Link(n2, n3);

  _links.push_front(l1_2);
  _links.push_front(l2_3);
}

Scene_Map::~Scene_Map() {}
