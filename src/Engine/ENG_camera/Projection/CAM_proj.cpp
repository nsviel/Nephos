#include "CAM_proj.h"

#include <Utility/UTL_window/UTL_window.h>


//Constructor / Destructor
CAM_proj::CAM_proj(UTL_window* utl_window){
  //---------------------------

  this->utl_window = utl_window;

  //---------------------------
}
CAM_proj::~CAM_proj(){}

//Main function
mat4 CAM_proj::compute_proj_perspective(Struct_camera* camera){
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float fov = glm::radians(camera->fov);

  vec2 window_dim = utl_window->get_window_dim();
  float ratio = window_dim.x / window_dim.y;

  mat4 cam_proj = perspective(fov, ratio, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}
mat4 CAM_proj::compute_proj_ortho(Struct_camera* camera){
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float zoom = camera->zoom;
  mat4 cam_proj = ortho(-5.f - zoom, 5.f + zoom, -5.f - zoom, 5.f + zoom, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}
