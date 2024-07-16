#pragma once

#include <IO/src/Format/PLY/Structure/Enum.h>


namespace io::importer{

struct Property{
  fmt::ply::Field field;
  fmt::ply::Type type;
  int size = 0;
};

}
