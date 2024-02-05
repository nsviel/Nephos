#pragma once

#include <string>
#include <vector>


namespace utl::media{

struct Image{
  //---------------------------

  int channel_nb = 4;
  int channel_byte = 1;
  int width;
  int height;
  int size;

  std::vector<uint8_t> buffer;
  std::string format;

  //---------------------------
};

}
