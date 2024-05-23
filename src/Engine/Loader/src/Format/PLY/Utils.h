#pragma once

#include <string>


namespace format::ply{

enum Format{
  ASCII = 0,
  BINARY_LITTLE_ENDIAN = 1,
  BINARY_BIG_ENDIAN = 2,
};

enum Type{
  FLOAT32 = 0,
  FLOAT64 = 1,
  UINT8 = 2,
  UINT16 = 3,
  UINT32 = 4,
  UCHAR = 5,
};

struct Property{
  format::ply::Type type;
  std::string name = "";
  int size = 0;
};

}
