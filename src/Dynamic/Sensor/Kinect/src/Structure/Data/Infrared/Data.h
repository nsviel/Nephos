#pragma once

#include <k4a/k4a.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace k4n::str::infra{

struct Data{
  //---------------------------

  std::vector<float> Is;        //Intensity
  std::string format = "";
  k4a::image image;
  float timestamp = -1;
  float temperature = -1;
  uint8_t* buffer = nullptr;
  int width = 0;
  int height = 0;
  int size = 0;

  //---------------------------
};

}
