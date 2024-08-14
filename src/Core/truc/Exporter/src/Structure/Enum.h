#pragma once


namespace io::exp{

enum Mode{
  EXPORT = 0,
  RECORD = 1,
};

enum Encoding{
  ASCII = 0,
  BINARY = 1,
};

enum Field{
  VOID = 0,
  XYZ = 1,
  NXYZ = 2,
  RGB = 3,
  I = 4,
  TS = 5,
};

}
