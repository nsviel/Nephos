#pragma once

#include <Utility/Base/Type/Element.h>
#include <string>
#include <vector>


namespace utl::media{

enum Type{
  COLOR = 0,
  DEPTH = 1,
  INTENSITY = 2,
  NORMAL = 3,
  TEXTURE = 4,
  RADIOMETRY = 5,
};

struct Image : public utl::base::Element{
  //---------------------------

  //Info
  int channel_nb = 4;
  int channel_byte = 1;
  int width = -1;
  int height = -1;
  int size = 0;
  int type = utl::media::COLOR;
  float timestamp = -1;

  //Texture
  int texture_ID = -1;
  void* gui_texture_ID;

  //Data
  std::vector<uint8_t> data;
  std::string format = "";
  std::string name = "";
  bool new_data = false;

  //---------------------------
};

}
