#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace k4n::structure{

struct Buffer{
  //---------------------------

  std::vector<glm::vec3> xyz;   //XYZ location
  std::vector<glm::vec3> rgb;   //RGB color
  std::vector<glm::vec4> rgba;  //Displayed color data
  std::vector<float> Is;        //Intensity
  std::vector<float> R;         //Range
  std::vector<float> H;         //Height

  //---------------------------
};

}
