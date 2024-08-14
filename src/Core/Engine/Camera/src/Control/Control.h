#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace cam{class Node;}
namespace cam::projection{class Perspective;}
namespace cam::mode{class Base;}
namespace cam{class Entity;}
namespace cam{class Structure;}
namespace utl::base{class Pose;}


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
std::string a = "hey";
  //Camera matrix
  glm::mat4 compute_camera_view();
  glm::mat4 compute_camera_proj();
  glm::mat4 compute_camera_mvp();
  void compute_camera_mvp(utl::base::Pose* pose);
  glm::mat4 compute_camera_pose();

  //Camera parameter
  void set_camera_COM(glm::vec3 value);
  void set_camera_mode(cam::Entity* camera);
  void set_camera_proj(cam::Entity* camera, int projection);
  void set_next_camera_mode();

private:
  cam::projection::Perspective* cam_perspective;
  cam::Structure* cam_struct;

  std::vector<cam::mode::Base*> vec_mode;
  cam::mode::Base* active_mode;
};

}