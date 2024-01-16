#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Base/Entity/Struct_entity.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <mutex>

class Engine;

namespace entity{
class Glyph;
class Data;


class Object : public entity::Entity
{
public:
  //Constructor / Destructor
  Object();
  Object(Engine* engine);
  ~Object();

  //Main function
  void update_entity();
  void remove_entity();
  void reset_entity();
  void visibility_entity(bool value);

  inline entity::Object* get_object(){return this;}

public:
  Engine* engine;

  utl::base::Data* data;
  std::list<entity::Glyph*> list_glyph;
};

}
