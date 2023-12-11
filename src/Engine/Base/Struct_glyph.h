#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Base/Struct_object.h>


namespace eng::structure{

struct Glyph : public eng::structure::Object
{
  //---------------------------

  bool is_permanent = false;
  eng::structure::Object* linked_object = nullptr;

  //---------------------------
};

}
