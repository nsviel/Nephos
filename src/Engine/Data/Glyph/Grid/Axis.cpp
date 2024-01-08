#include "Axis.h"


namespace glyph::grid{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->color = vec4(0.4f, 0.4f, 0.4f, 1.0f);
  this->nb_cell = 10;

  //---------------------------
}
Axis::~Axis(){
  //---------------------------

  delete data;

  //---------------------------
}

void Axis::create(){
  //---------------------------

  this->data = new eng::data::Object();
  data->draw_line_width = 2;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->is_suppressible = false;
  data->unicolor = color;
  this->update();

  //---------------------------
}
void Axis::update(){
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
