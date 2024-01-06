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

  delete data;

  //---------------------------
}

eng::data::Object* Grid_axis::create(){
  //---------------------------

  this->data = new eng::data::Object();
  data->draw_line_width = 5;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->unicolor = color;
  this->update();

  //---------------------------
  return data;
}
void Grid_axis::update(){
  vector<vec3>& XYZ = data->xyz;
  vector<vec4>& RGB = data->rgb;
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
