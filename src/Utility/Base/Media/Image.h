#pragma once

#include <Utility/Base/Data/Element.h>
#include <string>
#include <vector>


namespace utl::media{

struct Image : public utl::base::Element{
  //---------------------------

  Image(){};
  Image(std::string name){this->name = name;}

  //Info
  int channel_nb = 4;
  int channel_byte = 1;
  int width = -1;
  int height = -1;
  int size = 0;
  double timestamp = -1;

  //Texture
  int texture_ID = -1;
  void* gui_texture_ID;

  //Data
  std::vector<uint8_t> data;
  std::string format = "R8G8B8A8_SRGB";
  std::string name = "";

  //---------------------------
};

}
