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
  object->name = "camera";
  object->draw_line_width = 1;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_object.push_back(object);

  //---------------------------
}
void Target::update(eng::data::Object* object){
  //---------------------------



  //---------------------------
}

}
