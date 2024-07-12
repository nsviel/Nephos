#pragma once

#include <Utility/Namespace.h>
#include <string>


namespace format::ply{

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

struct Data{
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec3> rgb;
  std::vector<float> Is;
  std::vector<float> ts;
};

}
