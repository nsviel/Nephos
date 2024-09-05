#pragma once

#include <Importer/src/Structure/Enum.h>


namespace io::imp::structure{

struct Operation{
  //---------------------------

  float scaling = 1;
  bool with_centering = false;
  bool with_clearing = true;
  bool open_navigation = true;

  //---------------------------
};

}
