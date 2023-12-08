#pragma once

#include <UTL_base/Struct_object.h>


namespace data{

struct Glyph : public data::Object
{
  //---------------------------

  bool is_permanent = false;
  data::Object* linked_object = nullptr;

  //---------------------------
};

}
