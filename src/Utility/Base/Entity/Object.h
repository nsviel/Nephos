#pragma once

#include <Utility/Base/Type/Struct_data.h>
#include <Utility/Specific/common.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>

namespace eng{class Engine;}

namespace utl::entity{
class Glyph;


class Object : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Object();
  Object(eng::Engine* engine);
  ~Object();

  //Main function
  void update_entity();
  void remove_entity();
  void reset_entity();
  void visibility_entity(bool value);

  inline utl::type::Data* get_data(){return data;}
  inline utl::type::Pose* get_pose(){return pose;}

public:
  eng::Engine* engine;

  utl::type::Data* data;
  utl::type::Pose* pose;
  std::list<utl::entity::Glyph*> list_glyph;
};

}
