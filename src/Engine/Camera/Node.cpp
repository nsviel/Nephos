#include "Node.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  util::element::Window* utl_window = utility->get_utl_window();

  this->camera = new eng::data::Camera();
  this->cam_arcball = new eng::camera::mode::Arcball(utl_window);
  this->cam_fp = new eng::camera::mode::Player(utl_window);
  this->cam_zoom = new eng::camera::Zoom(utl_window);
  this->cam_proj = new eng::camera::Projection(utl_window);
  this->cam_control = new eng::camera::Control(engine, camera);

  this->arcball_origin = vec3(0, 0, 0);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete cam_arcball;
  delete cam_fp;
  delete cam_zoom;
  delete cam_proj;

  //---------------------------
}

//Main function
void Node::loop(){
  //---------------------------

  cam_control->control_mouse();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  camera->reset();

  //---------------------------
}

//MVP Matrix
mat4 Node::compute_cam_view(){
  mat4 cam_view;
  //---------------------------
/*
  if(camera->cam_pose){
    cam_view = camera->cam_pose_mat;
  }else if(camera->mode == "player"){
    cam_view = cam_fp->fp_view_mat(camera);
  }else if(camera->mode == "arcball"){
    camera->cam_COM_obj = arcball_origin;
    cam_view = cam_arcball->arcball_view_mat(camera);
  }
*/
  //---------------------------
  return cam_view;
}
mat4 Node::compute_cam_proj(){
  mat4 projection;
  //---------------------------

  if(camera->projection == "perspective"){
    projection = cam_proj->compute_proj_perspective(camera);
  }
  else if(camera->projection == "orthographic"){
    projection = cam_proj->compute_proj_ortho(camera);
  }

  //---------------------------
  return projection;
}
mat4 Node::compute_cam_mvp(){
  //---------------------------

  mat4 cam_modl = mat4(1);
  mat4 cam_view = compute_cam_view();
  mat4 cam_proj = compute_cam_proj();

  mat4 mvpMatrix = cam_proj * cam_view * cam_modl;

  //---------------------------
  return mvpMatrix;
}
void Node::compute_cam_mvp(eng::data::Object* object){
  if(object == nullptr) return;
  //---------------------------

  mat4 cam_modl = glm::transpose(object->model);
  mat4 cam_view = compute_cam_view();
  mat4 cam_proj = compute_cam_proj();

  object->mvp = cam_proj * cam_view * cam_modl;

  //---------------------------
}


}
