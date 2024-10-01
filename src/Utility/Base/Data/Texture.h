#pragma once

#include <Utility/Base/Data/Element.h>
#include <vector>
#include <string>


namespace utl::base{

template<typename T>
struct Texture : public utl::base::Element{
  //---------------------------

  Texture() = default;
  Texture(std::string name){this->name = name;}

  //Info
  int channel_nb = 4;
  int channel_byte = sizeof(T);
  int width = 0;
  int height = 0;
  int size = 0;

  //Data
  std::vector<T> data;
  std::string format = "RGBA8";
  std::string name = "default";

  //---------------------------
};

struct Storage : public utl::base::Texture<float> {
  //---------------------------

  Storage() = default;
  Storage(std::string name) : Texture(name) {}

  //---------------------------
};
struct Image : public utl::base::Texture<uint8_t> {
  //---------------------------

  Image() = default;
  Image(std::string name) : Texture(name) {}

  float timestamp = 0;

  //---------------------------
};

}
