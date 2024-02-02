#include "Camera.h"


namespace glyph::camera{

//Constructor / destructor
Camera::Camera(eng::Node* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->draw_line_width = 1;
  data->draw_type_name = "line";
  data->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_data.push_back(data);

  //---------------------------
}

}
