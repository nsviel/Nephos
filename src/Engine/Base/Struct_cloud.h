#pragma once

#include <Engine/Base/Struct_object.h>


namespace eng::structure{

struct Cloud : public eng::structure::Object
{
  //---------------------------

  eng::structure::Glyph aabb;
  eng::structure::Glyph axis;
  eng::structure::Glyph normal;
  eng::structure::Glyph tree;

  //---------------------------
};

}
