#pragma once


namespace utl::topology{

enum Type{
  POINT = 0,
  LINE = 1,
  LINE_STRIP = 2,
  TRIANGLE = 3,
  TRIANGLE_STRIP = 4,
  TRIANGLE_FAN = 5,
  QUAD = 6,
  DYNAMIC_POINT = 7,
};

}

namespace utl::base{

struct Topology{
  //---------------------------

  utl::topology::Type type = utl::topology::POINT;
  float width = 5.0f;

  //---------------------------
};

}
