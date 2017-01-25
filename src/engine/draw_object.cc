#include "draw_object.h"

bool Draw_Object::covers(float x, float y) {

  if ((_x <= x) && (x <= _x + _dim_x))
    if ((_y <= y) && (y <= _y + _dim_y))
      return true;

  return false;
};

Draw_Object::Draw_Object(){}
Draw_Object::~Draw_Object(){}
