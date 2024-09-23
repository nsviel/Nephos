#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace cam{class Node;}
namespace cam{class Structure;}
namespace cam{class Entity;}
namespace cam::projection{class Perspective;}
namespace cam::mode{class Base;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}
namespace vk::interface{class Window;}
namespace utl::base{class Pose;}


namespace cam{

class Control
{
public:
  Control(cam::Node* node_camera);
  ~Control();

public:
  //Main function
  void control_keyboard(int direction, bool fast);
  void control_mouse();
  void control_wheel(float value);
  void control_zoom(float value);

  //Camera parameter
  void set_camera_COM(glm::vec3 value);
  void set_camera_mode(std::shared_ptr<cam::Entity> camera);
  void set_camera_proj(std::shared_ptr<cam::Entity> camera, int projection);
  void set_next_camera_mode();

private:
  cam::Structure* cam_struct;
  cam::projection::Perspective* cam_perspective;
  vk::interface::Window* vk_window;
};

}
