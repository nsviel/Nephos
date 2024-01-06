#include "Grid_axis.h"


namespace glyph::world{

//Constructor / destructor
Grid_axis::Grid_axis(){
  //---------------------------

  this->color = vec4(1, 1, 1, 0.5);
  this->nb_cell = 40;

  //---------------------------
}
Grid_axis::~Grid_axis(){
  //---------------------------

  delete object;

  //---------------------------
}

eng::data::Object* Grid_axis::create(){
  //---------------------------

  this->object = new eng::data::Object();
  object->draw_line_width = 5;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color;
  this->update();

  //---------------------------
  return object;
}
void Grid_axis::update(){
  vector<vec3>& XYZ = object->xyz;
  vector<vec4>& RGB = object->rgb;
  //---------------------------

  //Parameters
  XYZ.clear();
  RGB.clear();

  //X axis
  XYZ.push_back(vec3(-nb_cell, 0, 0));
  XYZ.push_back(vec3(nb_cell, 0, 0));
  RGB.push_back(color);
  RGB.push_back(color);

  //Y axis
  XYZ.push_back(vec3(0, -nb_cell, 0.005));
  XYZ.push_back(vec3(0, nb_cell, 0.005));
  RGB.push_back(color);
  RGB.push_back(color);

  //---------------------------
}

}
