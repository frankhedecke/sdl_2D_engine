#include <iostream> // TODO remove
#include <random>
#include <vector>

#include "scene_map.h"
#include <SDL.h>

void Node::Node_Draw_Object::left_click() {

  // std::cout << "node at float-pos " << _x << " / " << _y << " is left clicked." << std::endl;
  if (_node != nullptr)
    _node->toggle_tex();
}

void Node::Node_Draw_Object::right_click() {

  // std::cout << "node at float-pos " << _x << " / " << _y << " is right clicked." << std::endl;
}

void Node::Node_Draw_Object::mouse_over() {

  if (_node != nullptr)
    _node->hi_tex();

  // std::cout << "node at float-pos " << _x << " / " << _y << " is hovered." << std::endl;
}

Node::Node(uint16_t x, uint16_t y, SDL_Texture* tex, SDL_Texture* tex_hi, SDL_Texture* tex_alt) : _pos_x(x), _pos_y(y), _tex(tex), _tex_hi(tex_hi), _tex_alt(tex_alt) {

  _obj._x = 0.1 + 0.05 * _pos_x;
  _obj._y = 0.1 + 0.05 * _pos_y;
  _obj._dim_x = 0.02;
  _obj._dim_y = 0.02;
  _obj._node = this;
  _obj._tex = _tex;

  _cur_tex = 0;
  _fill = 0;
  _diff_value = 0;
}

void Node::toggle_tex() {

  if (_cur_tex == 0) {
    _cur_tex = 1;
    _obj._tex = _tex_alt;
  } else {
    _cur_tex = 0;
    _obj._tex = _tex;
  }
};

void Node::hi_tex() {

  if (_cur_tex == 0) {
    _obj._tex = _tex_hi;
  }
};

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

  // std::cout << "Scene_Map::input()" << std::endl;

  if (event->type == SDL_KEYDOWN) {
    switch(event->key.keysym.sym) {
      case SDLK_w: _keys[0] = true; break;
      case SDLK_s: _keys[1] = true; break;
      case SDLK_a: _keys[2] = true; break;
      case SDLK_d: _keys[3] = true; break;
      case SDLK_f: _keys[4] = true; break; // TODO use _fullscreen_key in object scene
    }
  } else if (event->type == SDL_KEYUP) {
    // TODO check if buttons are pressed or already are released
    switch(event->key.keysym.sym) {
      case SDLK_w: _keys[0] = false; break;
      case SDLK_s: _keys[1] = false; break;
      case SDLK_a: _keys[2] = false; break;
      case SDLK_d: _keys[3] = false; break;
      case SDLK_f:
             if (_keys[4]) {
                _keys[4] = false;
                _screen->toggle_fullscreen();
             }
             break;
    }
  }
}

void Scene_Map::process() {

  // update
  ++_mod_ticks;

  if (_mod_ticks >= 1) {
  
    _mod_ticks = 0;
    std::cout << "tick " << SDL_GetTicks() << std::endl;
    std::cout << "mouse at pixels " << _mouse_pos_x << "|" << _mouse_pos_y << std::endl;

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
  _tex_square_hi = _screen->load_Texture("res/square_hi.png");
  _tex_square2 = _screen->load_Texture("res/square_green.png");
  _startup_ticks = SDL_GetTicks();
  _mod_ticks = 0;
  for (int i = 0; i < 5; ++i)
    _keys[i] = false;

  // create nodes
  Node* n1 = new Node(1, 3, _tex_square, _tex_square_hi, _tex_square2);
  Node* n2 = new Node(4, 4, _tex_square, _tex_square_hi, _tex_square2);
  Node* n3 = new Node(5, 5, _tex_square, _tex_square_hi, _tex_square2);

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

Scene_Map::~Scene_Map() {

  // TODO free textures
}
