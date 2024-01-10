#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Camera/Mode/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;


namespace eng::camera{

class Control
{
public:
  Control(Engine* engine, eng::data::Camera* camera);
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
  void compute_camera_mvp(eng::data::Object* object);
  mat4 compute_camera_pose();

private:
  eng::camera::Zoom* cam_zoom;
  eng::camera::Projection* cam_proj;
  
  vector<eng::camera::mode::Base*> vec_mode;
  eng::camera::mode::Base* active_mode;
  eng::data::Camera* camera;
};

}
