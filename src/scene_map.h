#pragma once
#include <forward_list>
#include <SDL.h>

#include <draw_object.h>
#include <object_scene.h>
#include <scene_manager.h>

class Node {

  class Node_Draw_Object : public Draw_Object {
    public:
      Node* _node;

      void left_click();
      void right_click();
      void mouse_over();
  };

  public:
    uint16_t _pos_x;
    uint16_t _cur_tex;
    uint16_t _pos_y;
    float _fill;
    float _diff_value;
    Node_Draw_Object _obj;
    SDL_Texture* _tex;
    SDL_Texture* _tex_hi;
    SDL_Texture* _tex_alt;

    Node(uint16_t x, uint16_t y, SDL_Texture* tex, SDL_Texture* tex_hi, SDL_Texture* tex_alt);
    void update();
    void clicked();
    void toggle_tex();
    void hi_tex();
};

class Link {

  private:
    float _resistance;

  public:
    Node* _origin1;
    Node* _origin2;

    void update();
    Link(Node* origin1, Node* origin2);
};

class Scene_Map : public Object_Scene {

  private:
    uint32_t _mod_ticks;
    uint32_t _startup_ticks;
    bool _keys[5];
    std::forward_list<Node*> _nodes;
    std::forward_list<Link*> _links;
    // textures
    SDL_Texture* _tex_bg;
    SDL_Texture* _tex_square;
    SDL_Texture* _tex_square_hi;
    SDL_Texture* _tex_square2;

    void input(SDL_Event* event);
    void process();

  public:
    Scene_Map(Scene_Manager* manager);
    ~Scene_Map();
    void pre_tick(bool &quit);
    void pre_draw();
    void post_draw();
};
