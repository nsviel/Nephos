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
  object->draw_line_width = 10;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_object.push_back(object);
  this->construct(object);

  //---------------------------
}
void Target::update(eng::data::Entity* entity){
  eng::data::Object* object = vec_object[0];
  //---------------------------

  if(eng::data::Camera* camera = dynamic_cast<eng::data::Camera*>(entity)){
sayHello();
  }

  //---------------------------
}
void Target::construct(eng::data::Object* object){
  vector<vec3>& XYZ = object->xyz;
  vector<vec4>& RGB = object->rgb;
  //---------------------------

  XYZ.clear();
  RGB.clear();

  //X axis
  XYZ.push_back(vec3(-1, 0, 0));
  XYZ.push_back(vec3(1, 0, 0));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, -1, 0));
  XYZ.push_back(vec3(0, 1, 0));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //---------------------------
}

}
