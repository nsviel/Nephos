#pragma once

#include <Data/src/Base/Entity.h>
#include <glm/glm.hpp>
#include <string>
#include <list>


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
