#pragma once

#include <Engine/Camera/src/Mode/Base.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

namespace eng::cam::mode{class Base;}


namespace eng::cam::mode{

class Player : public eng::cam::mode::Base
{
public:
  Player(eng::cam::Node* cam_node);
  ~Player();

public:
  //Camera movement
  void camera_forward(utl::entity::Camera* camera, float speed);
  void camera_backward(utl::entity::Camera* camera, float speed);
  void camera_right(utl::entity::Camera* camera, float speed);
  void camera_left(utl::entity::Camera* camera, float speed);
  void camera_up(utl::entity::Camera* camera, float speed);
  void camera_down(utl::entity::Camera* camera, float speed);
  void camera_mouse(utl::entity::Camera* camera);
  void camera_zoom(utl::entity::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(utl::entity::Camera* camera);

private:
  utl::element::Window* utl_window;
  
  vec2 mouse_pose_old;
};

}
