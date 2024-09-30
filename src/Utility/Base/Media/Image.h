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
  double timestamp = -1;
  bool display = true;
  int channel_nb = 4;
  int channel_byte = 1;
  int width = 1;
  int height = 1;
  int size = 0;

  //Data
  std::vector<uint8_t> data;
  std::string format = "RGBA8";
  std::string name = "default";

  //---------------------------
};

}
