#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace cam{class Node;}
namespace cam{class Projection;}
namespace cam::mode{class Base;}


namespace cam{

class Control
{
public:
  Control(cam::Node* node_camera);
  ~Control();

public:
  //Camera movement
  void control_keyboard(int direction, bool fast);
  void control_mouse();
  void control_wheel(float value);
  void control_zoom(float value);

  //Camera matrix
  mat4 compute_camera_view();
  mat4 compute_camera_proj();
  mat4 compute_camera_mvp();
  void compute_camera_mvp(utl::type::Pose* pose);
  mat4 compute_camera_pose();

  //Camera parameter
  void set_camera(utl::entity::Camera* camera);
  void set_camera_COM(vec3 value);
  void set_camera_mode(utl::entity::Camera* camera);
  void set_camera_proj(utl::entity::Camera* camera, int projection);
  void set_next_camera_mode();

private:
  cam::Projection* cam_proj;

  vector<cam::mode::Base*> vec_mode;
  cam::mode::Base* active_mode;
  utl::entity::Camera* camera = nullptr;
};

}
