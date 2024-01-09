#include "Axis.h"


namespace glyph::world{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->name = "Axis";
  this->is_visible = true;

  //---------------------------
}
Axis::~Axis(){
  //---------------------------

  delete data;

  //---------------------------
}

//Main function
void Axis::create(){
  //---------------------------

  data = new eng::data::Object();
  data->draw_line_width = 4;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->is_suppressible = false;
  this->update();

  //---------------------------
}
void Axis::update(){
  vector<vec3>& XYZ = data->xyz;
  vector<vec4>& RGB = data->rgb;
  float z = 0;
  //---------------------------

  //X axis
  XYZ.push_back(vec3(0, 0, z));
  XYZ.push_back(vec3(1, 0, z));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, 0, z));
  XYZ.push_back(vec3(0, 1, z));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  XYZ.push_back(vec3(0, 0, z));
  XYZ.push_back(vec3(0, 0, 1));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}

}
