#pragma once

#include <Loader/src/Base/Exporter.h>
#include <string>


namespace ldr::importer{

struct Structure{
  //---------------------------

  float scaling = 1;
  bool center = false;
  bool remove_old = true;

  //---------------------------
};

}
