#pragma once

#include <Loader/src/Base/Path.h>
#include <string>


namespace ldr::importer{

struct Structure{
  //---------------------------

  ldr::base::Path path;
  float scaling = 1;
  bool center = false;
  bool remove_old = true;

  //---------------------------
};

}
