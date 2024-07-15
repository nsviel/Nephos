#pragma once

#include <IO/src/Import/Structure/Structure.h>
#include <IO/src/Export/Structure/Structure.h>
#include <IO/src/Transformation/Structure.h>


namespace ldr{

struct Structure{
  //---------------------------

  ldr::importer::Structure importer;
  ldr::exporter::Structure exporter;
  ldr::transformation::Structure transformation;

  //---------------------------
};

}
