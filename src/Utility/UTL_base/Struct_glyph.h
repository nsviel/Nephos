#pragma once

#include <UTL_base/Struct_object.h>


namespace data{

struct Glyph : public Object
{
  //---------------------------

  bool is_permanent = false;
  Object* linked_object = nullptr;

  //---------------------------
};

}
