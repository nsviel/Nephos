#pragma once

#include <Loader/src/Format/PLY/Structure/Enum.h>


namespace fmt::ply{

struct Property{
  fmt::ply::Field field;
  fmt::ply::Type type;
  int size = 0;
};

}
