#pragma once

#include <k4a/k4a.hpp>


namespace k4n::structure{

struct Cloud{
  //---------------------------

  std::vector<glm::vec2> table_xy;
  k4a::image k4a_image;
  k4a_calibration_type_t calibration_type;
  uint8_t* buffer = nullptr;
  int width = 0;
  int height = 0;
  int size = 0;

  //---------------------------
};

}
