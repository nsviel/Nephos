#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace cam{class Node;}
namespace cam{class Projection;}
namespace cam::mode{class Base;}
namespace cam{class Entity;}
namespace cam{class Structure;}
namespace utl::type{class Pose;}


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
  glm::mat4 compute_camera_view();
  glm::mat4 compute_camera_proj();
  glm::mat4 compute_camera_mvp();
  void compute_camera_mvp(utl::type::Pose* pose);
  glm::mat4 compute_camera_pose();

  //Camera parameter
  void set_camera_COM(glm::vec3 value);
  void set_camera_mode(cam::Entity* camera);
  void set_camera_proj(cam::Entity* camera, int projection);
  void set_next_camera_mode();

private:
  cam::Projection* cam_proj;
  cam::Structure* cam_struct;

  std::vector<cam::mode::Base*> vec_mode;
  cam::mode::Base* active_mode;
};

}
