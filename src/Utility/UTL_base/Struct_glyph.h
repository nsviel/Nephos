#pragma once

#include <UTL_base/Struct_object.h>


namespace data{

struct Glyph : public Object
{
  //---------------------------

  Glyph();

  bool is_permanent;
  Object* linked_object;

  //---------------------------
};

}
