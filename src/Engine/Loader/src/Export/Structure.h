#pragma once

#include <Loader/src/Base/Exporter.h>
#include <string>


namespace ldr::exporter{

struct Structure{
  //---------------------------

  int encoding = ldr::io::BINARY;
  bool transformed = false;

  //---------------------------
};

}
