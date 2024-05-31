#pragma once

#include <Data/src/Base/Entity.h>
#include <Utility/Base/Type/Data.h>
#include <glm/glm.hpp>
#include <string>
#include <list>

namespace vk{class Node;}
namespace eng{class Node;}
namespace cam{class Node;}
namespace dat::base{class Glyph;}
namespace dat{class Entity;}


namespace dat::object::glyph{
enum Glyph{
  AABB = 0,
  AXIS = 1,
  NORMAL = 2,
  TREE = 3,
};
}

namespace dat::base{

class Object : public dat::base::Entity
{
public:
  //Constructor / Destructor
  Object();
  Object(eng::Node* node_engine);
  ~Object();

  //Herited function
  void reset();
  void remove();
  void update_pose();
  void visibility(bool value);

  //New function
  void clear_data();
  void update_glyph();
  dat::base::Glyph* get_glyph(int type);

public:
  //Dependancy
  vk::Node* node_vulkan;
  cam::Node* node_camera = nullptr;
  dat::Entity* dat_entity;
};

}
