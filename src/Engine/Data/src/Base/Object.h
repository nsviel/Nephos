#pragma once

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Data/Namespace.h>

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


namespace dat::object{
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
  Object(){
    //---------------------------

    this->entity_type = "entity::Object";
    this->data.unicolor = math::random();

    //---------------------------
  }
  ~Object(){}

public:
};

}
