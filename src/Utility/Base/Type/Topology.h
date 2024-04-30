#pragma once


namespace utl::topology{

enum Type{
  POINT = 0,
  LINE = 1,
  TRIANGLE = 2,
  QUAD = 3,
};

}

namespace utl::type{

struct Topology{
  //---------------------------

  int type = utl::topology::POINT;
  int width = 5;

  //---------------------------
};

}
