#pragma once

#include <IO/src/Import/Structure/Structure.h>
#include <IO/src/Export/Structure/Structure.h>
#include <IO/src/Transformation/Structure.h>


namespace io{

struct Structure{
  //---------------------------

  io::importer::Structure importer;
  io::exporter::Structure exporter;
  io::transformation::Structure transformation;

  //---------------------------
};

}
