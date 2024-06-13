#pragma once

#include <string>


namespace ldr::exporter{

struct Structure{
  //---------------------------

  int encoding = ldr::io::BINARY;
  bool transformed = false;

  //---------------------------
};

}
