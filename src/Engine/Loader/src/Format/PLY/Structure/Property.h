#pragma once


namespace fmt::ply{

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
  XYZ = 1,
  NXYZ = 2,
  RGB = 3,
  I = 4,
  TS = 5,
};

struct Property{
  fmt::ply::Field field;
  fmt::ply::Type type;
  int size = 0;
};

}
