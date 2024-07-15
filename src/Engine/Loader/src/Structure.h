#pragma once

#include <Loader/src/Import/Structure/Structure.h>
#include <Loader/src/Export/Structure/Structure.h>
#include <Loader/src/Transformation/Structure.h>


namespace ldr{

struct Structure{
  //---------------------------

  ldr::importer::Structure importer;
  ldr::exporter::Structure exporter;
  ldr::transformation::Structure transformation;

  //---------------------------
};

}
