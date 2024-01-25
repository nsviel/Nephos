#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

namespace eng{class Engine;}
namespace eng::cam{class Node;}
namespace eng::cam{class Projection;}
namespace eng::cam::mode{class Base;}


namespace eng::cam{

class Control
{
public:
  Control(eng::cam::Node* node_camera);
  ~Control();

public:
  //Camera movement
  void control_keyboard(int direction, bool fast);
  void control_mouse();
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
  void set_camera_mode();
  void set_next_camera_mode();

private:
  eng::cam::Projection* cam_proj;

  vector<eng::cam::mode::Base*> vec_mode;
  eng::cam::mode::Base* active_mode;
  utl::entity::Camera* camera;
};

}
