#pragma once

#include <IO/src/Import/Structure/Enum.h>


namespace io::importer{

struct Property{
  io::importer::Field field;
  io::importer::Type type;
  int size = 0;
};

}
