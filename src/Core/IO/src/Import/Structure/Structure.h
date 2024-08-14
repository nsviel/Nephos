#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>


namespace io::importer{

struct Structure{
  //---------------------------

  utl::base::Path path;
  float scaling = 1;
  bool with_centering = false;
  bool with_clearing = true;

  //---------------------------
};

}
