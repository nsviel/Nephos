#pragma once

#include <k4a/k4a.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace k4n::str::depth{

struct Data{
  //---------------------------

  std::vector<glm::vec3> xyz;   //XYZ location
  std::vector<float> R;         //Range
  std::vector<float> H;         //Height
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
