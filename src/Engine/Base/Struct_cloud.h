#pragma once

#include <Engine/Base/Struct_object.h>
#include <list>


namespace eng::structure{

struct Cloud : public eng::structure::Object
{
  //---------------------------

  eng::structure::Object aabb;
  eng::structure::Object axis;
  eng::structure::Object normal;
  eng::structure::Object tree;
  eng::structure::Object camera;

  std::list<eng::structure::Object*> list_glyph;

  //---------------------------
};

}
