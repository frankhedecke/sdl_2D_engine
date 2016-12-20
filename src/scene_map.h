#pragma once
#include <forward_list>
#include <SDL.h>

#include <draw_object.h>
#include <object_scene.h>
#include <scene_manager.h>

class Node {

  class Node_Draw_Object : public Draw_Object {
    void left_click();
    void mouse_over();
  };

  public:
    uint16_t _pos_x;
    uint16_t _pos_y;
    float _fill;
    float _diff_value;
    Node_Draw_Object _obj;

    Node(uint16_t x, uint16_t y, SDL_Texture* tex);
    void update();
    void clicked();
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
    // TODO move moue to class scene
    bool _click_left;
    bool _click_right;
    int _mouse_x;
    int _mouse_y;
    uint32_t _mod_ticks;
    uint32_t _startup_ticks;
    bool _keys[5];
    std::forward_list<Node*> _nodes;
    std::forward_list<Link*> _links;
    // textures
    SDL_Texture* _tex_bg;
    SDL_Texture* _tex_square;

    void input(SDL_Event* event);
    void process();
    void output();

  public:
    Scene_Map(Scene_Manager* manager);
    ~Scene_Map();
    void pre_tick(bool &quit);
    void post_tick(bool &quit);
};
