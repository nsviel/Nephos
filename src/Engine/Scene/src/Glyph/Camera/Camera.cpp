#include "Camera.h"


namespace glyph::camera{

//Constructor / destructor
Camera::Camera(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "cam::object";
  this->is_permanent = true;

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->name = "cam::object::data";
  data->width = 1;
  data->topology.type = utl::topology::LINE;
  data->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_data.push_back(data);

  //---------------------------
}

}
