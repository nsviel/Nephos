#pragma once

#include <Utility/Base/Data/Element.h>
#include <vector>
#include <string>


namespace utl::base{

struct Texture : public utl::base::Element{
  //---------------------------

  Texture() = default;
  Texture(std::string name){this->name = name;}

  //Info
  int channel_nb = 4;
  int width = 0;
  int height = 0;
  int size = 0;

  //Data
  std::string format = "RGBA8";
  std::string name = "default";

  //---------------------------
};

template<typename T>
struct Texture_data : public utl::base::Texture{
  //---------------------------

  Texture_data() = default;
  Texture_data(std::string name) : Texture(name){}

  int channel_byte = sizeof(T);
  std::vector<T> data;

  //---------------------------
};

struct Storage : public utl::base::Texture_data<float> {
  //---------------------------

  Storage() = default;
  Storage(std::string name) : Texture_data(name){}

  //---------------------------
};
struct Image : public utl::base::Texture_data<uint8_t> {
  //---------------------------

  Image() = default;
  Image(std::string name) : Texture_data(name){}

  float timestamp = 0;

  //---------------------------
};
struct Depth : public utl::base::Texture_data<uint16_t> {
  //---------------------------

  Depth() = default;
  Depth(std::string name) : Texture_data(name){}

  //---------------------------
};

}
