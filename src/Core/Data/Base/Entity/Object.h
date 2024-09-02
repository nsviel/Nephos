#pragma once

#include <Utility/Namespace.h>
#include <Element/src/Glyph/Object/AABB.h>
#include <Element/src/Glyph/Object/Axis.h>
#include <Element/src/Glyph/Object/Normal.h>
#include <Data/Base/Element/Entity.h>
#include <glm/glm.hpp>
#include <string>
#include <list>


namespace dat::base{

namespace object{
  enum Glyph{
    AABB = 0,
    AXIS = 1,
    NORMAL = 2,
    TREE = 3,
  };
}

struct Object : public dat::base::Entity{

  //Function
  Object(){
    //---------------------------

    this->data.unicolor = math::random();
    this->list_glyph.push_back(std::make_shared<dat::glyph::object::Axis>());
    this->list_glyph.push_back(std::make_shared<dat::glyph::object::AABB>());
    this->list_glyph.push_back(std::make_shared<dat::glyph::object::Normal>());
    this->type_entity = "object";

    //---------------------------
  }
  virtual ~Object(){}



};

}
