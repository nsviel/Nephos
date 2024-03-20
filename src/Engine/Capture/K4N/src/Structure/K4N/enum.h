#pragma once


namespace k4n::image{

enum Resolution{
  OFF = 0,
  P720 = 1,
  P1080 = 2,
  P1440 = 3,
  P1536 = 4,
  P2160 = 5,
  P3072 = 6,
};

enum Format{
  MJPG = 0,
  NV12 = 1,
  YUY2 = 2,
  BGRA32 = 3,
  DEPTH16 = 4,
  IR16 = 5,
  CUSTOM = 6,
};

}
