#pragma once

#include <Loader/src/Base/Exporter.h>
#include <Utility/Base/Data/Path.h>
#include <string>


namespace ldr::exporter{

struct Structure{
  //---------------------------

  utl::base::Path path;
  int encoding = ldr::io::BINARY;
  bool transformed = false;
  bool current_colorization = false;

  //---------------------------
};

}
