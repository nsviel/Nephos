#pragma once

#include <string>


namespace data{

struct data::Struct_image{
  //---------------------------

  int channel_nb = 4;
  int channel_byte = 1;
  int width;
  int height;
  uint8_t* buffer;
  std::string format;

  //---------------------------
};

}
