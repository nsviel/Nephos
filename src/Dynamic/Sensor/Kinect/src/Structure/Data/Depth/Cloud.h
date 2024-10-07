#pragma once

#include <k4a/k4a.hpp>


namespace k4n::str::depth{

struct Cloud{
  //---------------------------

  k4a::image image;
  uint8_t* buffer = nullptr;
  int width = 0;
  int height = 0;
  int size = 0;

  //---------------------------
};

}
