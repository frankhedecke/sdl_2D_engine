#pragma once
#include <forward_list>

#include "scene_manager.h"
#include "draw_object.h"

class Scene_Manager;

class Object_Scene : Scene{

  private:
    std::forward_list<Draw_Object*> _objects;

  public:
    Object_Scene(Scene_Manager* manager);
    ~Object_Scene();
    virtual void pre_tick(bool &quit) = 0;
    void tick(bool &quit);
    virtual void post_tick(bool &quit) = 0;
    void add_object(Draw_Object* object);
    void left_click(float x, float y);
};