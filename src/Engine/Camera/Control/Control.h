#pragma once


#include <Engine/Camera/Namespace.h>
#include <Engine/Camera/Mode/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;

namespace eng::camera{


class Control
{
public:
  Control(Engine* engine);
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
  void set_camera(entity::Camera* camera);
  void set_camera_COM(vec3 value);
  void set_camera_mode();
  void set_next_camera_mode();

private:
  eng::camera::Projection* cam_proj;

  vector<eng::camera::mode::Base*> vec_mode;
  eng::camera::mode::Base* active_mode;
  entity::Camera* camera;
};

}
