#pragma once

#include <Engine/Base/Struct_object.h>
#include <Utility/UTL_base/Struct_object.h>


namespace data{

struct Glyph : public eng::structure::Object
{
  //---------------------------

  bool is_permanent = false;
  eng::structure::Object* linked_object = nullptr;

  //---------------------------
};

}
