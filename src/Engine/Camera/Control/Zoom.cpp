#include "Zoom.h"


namespace eng::camera{

//Constructor / Destructor
Zoom::Zoom(util::element::Window* utl_window){
  //---------------------------

  //---------------------------
}
Zoom::~Zoom(){}

void Zoom::compute_zoom_optic(eng::data::Camera* camera, float yoffset){
  //---------------------------

  //Perspective zoom
  float camFOV = 65;
  if(camera->fov >= 1.0f && camera->fov <= camFOV) camera->fov -= yoffset;
  if(camera->fov <= 1.0f) camera->fov = 1.0f;
  if(camera->fov >= camFOV) camera->fov = camFOV;

  //Ortho zoom
  camera->zoom -= yoffset * 0.1;

  //---------------------------
}
void Zoom::compute_zoom_position(eng::data::Camera* camera, float yoffset){
  //---------------------------

  //Perspective zoom
  vec3 cam_forwardMove = camera->cam_F * yoffset * camera->speed_move * vec3(0.1,0.1,0.1);
  camera->cam_P += cam_forwardMove;

  //Ortho zoom
  camera->zoom -= yoffset * 0.1;

  //---------------------------
}

}
