#pragma once

#include <Utility/Namespace.h>
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
  USHORT = 6,
};

enum Field{
  VOID = 0,
  X = 1,
  Y = 2,
  Z = 3,
  NX = 4,
  NY = 5,
  NZ = 6,
  R = 7,
  G = 8,
  B = 9,
  I = 10,
  TS = 11,
};

struct Property{
  format::ply::Field field;
  format::ply::Type type;
  int size = 0;
};

struct Header{
  std::string path = "";
  std::vector<format::ply::Property> vec_property;
  utl::topology::Type topology = utl::topology::POINT;
  int format = format::ply::ASCII;
  int nb_point = 0;
  int nb_face = 0;
};

}
