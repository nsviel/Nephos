#pragma once

#include <Engine/Base/Struct_object.h>
#include <Engine/Base/Namespace.h>


namespace data{

struct Glyph : public eng::structure::Object
{
  //---------------------------

  bool is_permanent = false;
  eng::structure::Object* linked_object = nullptr;

  //---------------------------
};

}
