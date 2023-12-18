#pragma once

#include <Engine/Base/Struct_object.h>


namespace eng::structure{

struct Cloud : public eng::structure::Object
{
  //---------------------------

  std::list<eng::structure::Glyph*> list_glyph;

  //---------------------------
};

}
