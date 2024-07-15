#pragma once

#include <Loader/src/Export/Structure/Exporter.h>
#include <Utility/Base/Data/Path.h>
#include <string>


namespace ldr::exporter{

struct Structure{
  //---------------------------

  ldr::exporter::Encoding encoding = ldr::exporter::BINARY;
  utl::base::Path path;
  bool with_transformation = false;
  bool with_colorization = false;

  //---------------------------
};

}
