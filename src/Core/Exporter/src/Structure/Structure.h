#pragma once

#include <IO/src/Export/Structure/Base.h>
#include <Utility/Base/Data/Path.h>
#include <string>


namespace io::exporter{

struct Structure{
  //---------------------------

  io::exporter::Encoding encoding = io::exporter::BINARY;
  utl::base::Path path;
  bool with_transformation = false;
  bool with_colorization = false;

  //---------------------------
};

}
