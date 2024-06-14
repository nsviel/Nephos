#pragma once

#include <Loader/src/Base/Exporter.h>
#include <Loader/src/Base/Path.h>
#include <string>


namespace ldr::exporter{

struct Structure{
  //---------------------------

  ldr::base::Path path;
  int encoding = ldr::io::BINARY;
  bool transformed = false;
  bool current_colorization = false;

  //---------------------------
};

}
