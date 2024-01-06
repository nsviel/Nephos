#include "Camera.h"


namespace glyph::object{

//Constructor / destructor
Camera::Camera(){
  //---------------------------


  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(){
  //---------------------------

  data = new eng::data::Object();
  data->name = "camera";
  data->draw_line_width = 1;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->unicolor = vec4(1, 1, 1, 0.2f);

  //---------------------------
}
void Camera::update(eng::data::Object* object){
  //---------------------------



  //---------------------------
}

}
