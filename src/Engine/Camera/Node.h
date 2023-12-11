#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Mode/Namespace.h>
#include <Engine/Camera/Projection/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;


namespace eng::camera{

class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void control(string what, bool fast);
  void loop_cam_mouse();
  void reset();

  //MVP matrices
  mat4 compute_cam_view();
  void compute_cam_mvp(eng::structure::Object* object);
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
  inline eng::structure::Camera* get_camera(){return camera;};

private:
  Engine* engine;
  eng::camera::mode::Arcball* cam_arcball;
  eng::camera::mode::First_person* cam_fp;
  eng::camera::proj::Zoom* cam_zoom;
  eng::camera::proj::Projection* cam_proj;

  eng::structure::Camera* camera;
  vec3 arcball_origin;
};

}
