#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>


namespace io::imp{

struct Structure{
  //---------------------------

  utl::base::Path path;
  float scaling = 1;
  bool with_centering = false;
  bool with_clearing = true;
  bool open_navigation = true;;

  //---------------------------
};

}
