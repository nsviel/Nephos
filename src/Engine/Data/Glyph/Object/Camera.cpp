#include "Camera.h"


namespace glyph::object{

//Constructor / destructor
Camera::Camera(){
  //---------------------------


  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::create(eng::structure::Cloud* cloud){
  //---------------------------

  cloud->camera.name = "camera";
  cloud->camera.draw_line_width = 1;
  cloud->camera.is_visible = true;
  cloud->camera.draw_type_name = "line";
  cloud->camera.is_permanent = true;
  cloud->camera.unicolor = vec4(1, 1, 1, 0.2f);

  //---------------------------
}
void Camera::update(eng::structure::Cloud* cloud){
  //---------------------------



  //---------------------------
}

}
