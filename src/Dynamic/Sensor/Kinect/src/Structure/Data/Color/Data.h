#pragma once

#include <k4a/k4a.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace k4n::str::color{

struct Data{
  //---------------------------

  std::vector<glm::vec3> rgb;   //RGB color
  std::vector<glm::vec4> rgba;  //Displayed color data
  std::string format = "";
  k4a::image image;
  float timestamp = -1;
  uint8_t* buffer = nullptr;
  int width = 0;
  int height = 0;
  int size = 0;

  //---------------------------
};

}
