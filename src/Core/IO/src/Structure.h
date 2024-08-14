#pragma once

#include <IO/src/Export/Structure/Structure.h>
#include <IO/src/Transformation/Structure.h>


namespace io{

struct Structure{
  //---------------------------

  io::exporter::Structure exporter;
  io::transformation::Structure transformation;

  //---------------------------
};

}
