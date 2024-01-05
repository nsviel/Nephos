#include "Axis.h"


namespace glyph::world{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->name = "axis_world";
  this->is_visible = true;

  //---------------------------
}
Axis::~Axis(){
  //---------------------------

  delete glyph;

  //---------------------------
}

//Main function
void Axis::create(){
  //---------------------------

  glyph = new eng::structure::Glyph();
  glyph->draw_line_width = 4;
  glyph->is_visible = true;
  glyph->draw_type_name = "line";
  glyph->is_permanent = true;
  this->update();

  //---------------------------
}
void Axis::update(){
  vector<vec3>& XYZ = glyph->xyz;
  vector<vec4>& RGB = glyph->rgb;
  //---------------------------

  //X axis
  XYZ.push_back(vec3(0, 0, 0.005));
  XYZ.push_back(vec3(1, 0, 0.005));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, 0, 0.005));
  XYZ.push_back(vec3(0, 1, 0.005));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  XYZ.push_back(vec3(0, 0, 0.005));
  XYZ.push_back(vec3(0, 0, 1));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}

}
