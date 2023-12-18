#pragma once

#include <Engine/Base/Struct_object.h>
#include <list>


namespace eng::structure{

struct Cloud : public eng::structure::Object
{
  //---------------------------

  eng::structure::Glyph aabb;
  eng::structure::Glyph axis;
  eng::structure::Glyph normal;
  eng::structure::Glyph tree;
  eng::structure::Glyph camera;

  std::list<eng::structure::Glyph*> list_glyph;

  //---------------------------
};

}
