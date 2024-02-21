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
  data->line.width = 1;
  data->draw_type = utl::topology::LINE;
  data->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_data.push_back(data);

  //---------------------------
}

}
