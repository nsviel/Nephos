#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace cam{class Node;}
namespace cam::projection{class Perspective;}
namespace cam::mode{class Base;}
namespace cam{class Entity;}
namespace cam{class Structure;}
namespace utl::base{class Pose;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}
namespace vk::interface{class Window;}


namespace cam{

class MVP
{
public:
  MVP(cam::Node* node_camera);
  ~MVP();

public:
  //Main function
  void update_mvp();

  //Subfunction
  glm::mat4 compute_camera_view();
  glm::mat4 compute_camera_proj();
  glm::mat4 compute_camera_mvp();
  glm::mat4 compute_camera_pose();

private:
  cam::projection::Perspective* cam_perspective;
  cam::Structure* cam_struct;
  vk::interface::Window* vk_window;
};

}
