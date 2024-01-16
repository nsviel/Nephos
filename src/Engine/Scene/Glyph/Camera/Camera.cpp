#include "Camera.h"


namespace glyph::camera{

//Constructor / destructor
Camera::Camera(Engine* engine) : Glyph(engine){
  //---------------------------


  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->name = "camera";
  object->data->draw_line_width = 1;
  object->is_visible = true;
  object->data->draw_type_name = "line";
  object->is_permanent = true;
  object->data->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_object.push_back(object);

  //---------------------------
}
void Camera::update_glyph(entity::Entity* entity){
  //---------------------------



  //---------------------------
}

}
