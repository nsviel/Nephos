#pragma once

#include <Utility/Namespace.h>
#include <k4a/k4a.hpp>
#include <memory>

namespace k4n::structure{class Data;}
namespace utl::media{class Image;}
namespace utl::media{class Storage;}


namespace k4n::colornew{

struct Structure{
  //---------------------------

  k4n::base::Sensor* sensor;
  k4a::image image;
  std::string format = "";
  uint8_t* buffer;
  float timestamp = 0;
  int size = 0;
  int width = 0;
  int height = 0;

  //---------------------------
};

}
