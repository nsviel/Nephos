#pragma once

#include <Data/src/Glyph/Object/AABB.h>
#include <Data/src/Glyph/Object/Axis.h>
#include <Data/src/Glyph/Object/Normal.h>
#include <Data/src/Base/Entity.h>
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
  //---------------------------

  //Function
  Object(){
    //---------------------------

    this->entity_type = "entity::Object";
    this->data.unicolor = math::random();

    //this->list_glyph.push_back(new dat::glyph::object::Axis());
    //this->list_glyph.push_back(new dat::glyph::object::AABB());
    //this->list_glyph.push_back(new dat::glyph::object::Normal());

    //---------------------------
  }
  virtual ~Object(){}



  //---------------------------
};

}
