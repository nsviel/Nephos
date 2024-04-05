#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Specific/Common.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>

namespace vk{class Node;}
namespace eng{class Node;}
namespace eng::cam{class Node;}
namespace utl::entity{class Glyph;}


namespace utl::entity::object{
enum Glyph{
  AABB = 0,
  AXIS = 1,
  NORMAL = 2,
  TREE = 3,
};
}

namespace utl::entity{

class Object : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Object();
  Object(eng::Node* node_engine);
  ~Object();

  //Main function
  void clear_data();
  void update_data();
  void update_pose();
  void update_glyph();
  void remove_entity() override;
  void reset_entity();

  //Subfunction
  void set_visibility(bool value);
  utl::entity::Glyph* get_glyph(int type);

public:
  //Dependancy
  vk::Node* node_vulkan;
  eng::cam::Node* node_camera;
};

}
