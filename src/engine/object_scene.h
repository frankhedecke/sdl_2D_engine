#pragma once
#include <forward_list>

#include "scene.h"
#include "scene_manager.h"
#include "draw_object.h"

class Scene_Manager;

class Object_Scene : public virtual Scene {

  private:
    // TODO delte _objects
    std::forward_list<Draw_Object*> _objects;
    std::forward_list<Draw_Object*> _draw_objects;
    std::forward_list<Draw_Object*> _mouse_objects;

  public:
    Object_Scene(Scene_Manager* manager);
    ~Object_Scene();
    void tick(bool &quit);
    // TODO rename pre_tick()
    virtual void pre_tick(bool &quit) = 0;
    virtual void pre_draw() = 0;
    virtual void post_draw() = 0;
    void add_object(Draw_Object* object);
    void left_click(float x, float y);
    void right_click(float x, float y);
    void mouse_over(float x, float y);
};
