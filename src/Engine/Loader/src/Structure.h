#pragma once

#include <Loader/src/Base/Exporter.h>


namespace ldr{

struct Structure{
  //---------------------------

  //Import
  float import_scaling = 1;
  bool import_center = false;
  bool import_remove_old = true;

  //Export
  int export_encoding = ldr::io::BINARY;

  //---------------------------
};

}
