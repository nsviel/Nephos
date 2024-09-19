#pragma once


namespace utl::topology{

enum Type{
  POINT = 0,
  LINE = 1,
  TRIANGLE = 2,
  QUAD = 3,
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
