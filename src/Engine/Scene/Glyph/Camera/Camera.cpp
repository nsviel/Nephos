#include "Camera.h"


namespace glyph::camera{

//Constructor / destructor
Camera::Camera(Engine* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->data->draw_line_width = 1;
  object->data->draw_type_name = "line";
  object->data->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_data.push_back(object);

  //---------------------------
}
void Camera::update_glyph(entity::Entity* entity){
  //---------------------------



  //---------------------------
}

}
