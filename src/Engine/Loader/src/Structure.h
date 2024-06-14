#pragma once

#include <Loader/src/Import/Structure.h>
#include <Loader/src/Export/Structure.h>
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
