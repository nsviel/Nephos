#include "Target.h"


namespace glyph::camera{

//Constructor / destructor
Target::Target(){
  //---------------------------


  //---------------------------
}
Target::~Target(){}

//Main function
void Target::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  eng::data::Object* object = new eng::data::Object();
  object->name = "camera_target";
  object->draw_line_width = 1;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_object.push_back(object);

  //---------------------------
}
void Target::update(eng::data::Object* object){
  vector<vec3>& XYZ = vec_object[0]->xyz;
  vector<vec4>& RGB = vec_object[0]->rgb;
  //---------------------------

  //X axis
  XYZ.push_back(vec3(0, 0, 0));
  XYZ.push_back(vec3(1, 0, 0));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, 0, 0));
  XYZ.push_back(vec3(0, 1, 0));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //---------------------------
}

}
