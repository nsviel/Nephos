#include "Camera.h"


namespace glyph::object{

//Constructor / destructor
Camera::Camera(){
  //---------------------------


  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(eng::structure::Object* object){
  //---------------------------

  object->camera = new eng::structure::Object();
  eng::structure::Object* camera = object->camera;

  camera->name = "camera";
  camera->draw_line_width = 1;
  camera->is_visible = true;
  camera->draw_type_name = "line";
  camera->is_permanent = true;
  camera->unicolor = vec4(1, 1, 1, 0.2f);

  //---------------------------
}
void Camera::update(eng::structure::Object* object){
  //---------------------------



  //---------------------------
}

}
