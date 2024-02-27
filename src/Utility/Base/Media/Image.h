#pragma once

#include <string>
#include <vector>


namespace utl::media{

struct Image{
  //---------------------------

  //Info
  int channel_nb = 4;
  int channel_byte = 1;
  int width;
  int height;
  int size;

  //Texture
  int texture_ID = -1;
  void* gui_texture_ID;

  //Data
  std::vector<uint8_t> data;
  std::string format;
  bool new_data;

  //---------------------------
};

}
