#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Camera/Mode/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;

namespace eng::camera{
class Control;


class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function

  void loop_cam_mouse();
  void reset();

  //MVP matrices
  mat4 compute_cam_view();
  void compute_cam_mvp(eng::data::Object* object);
  mat4 compute_cam_proj();
  mat4 compute_cam_mvp();

  //Camera mode
  void set_mode_projection(int value);
  void set_mode_angle(int value);
  void set_mode_view(int value);

  //Specific function
  mat4 compute_cam_world_pose();
  void compute_zoom(float value);

  inline mat4 get_cam_view(){return compute_cam_view();}
  inline mat4 get_cam_proj(){return compute_cam_proj();}
  inline mat4 get_mvpMatrix(){return compute_cam_mvp();}
  inline eng::data::Camera* get_camera(){return camera;};
  inline eng::camera::Control* get_camera_control(){return cam_control;}

private:
  Engine* engine;
  eng::camera::mode::Arcball* cam_arcball;
  eng::camera::mode::First_person* cam_fp;
  eng::camera::Zoom* cam_zoom;
  eng::camera::Projection* cam_proj;
  eng::camera::Control* cam_control;

  eng::data::Camera* camera;
  vec3 arcball_origin;
};

}
