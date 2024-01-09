#include "Axis.h"


namespace glyph::world{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->name = "Axis";
  this->is_visible = true;

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  eng::data::Object* object = new eng::data::Object();
  object->draw_line_width = 4;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->is_suppressible = false;
  this->vec_object.push_back(object);
  this->update();

  //---------------------------
}
void Axis::update(){
  vector<vec3>& XYZ = vec_object[0]->xyz;
  vector<vec4>& RGB = vec_object[0]->rgb;
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
