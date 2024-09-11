#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace rlx::base{

struct Buffer{
  //---------------------------

  std::vector<glm::vec3> xyz;   //XYZ location
  std::vector<glm::vec3> rgb;   //RGB color
  std::vector<glm::vec4> rgba;  //Displayed color data
  std::vector<glm::vec2> uv;    //Texture coordinate
  std::vector<float> Is;        //Intensity
  std::vector<float> R;         //Range
  std::vector<float> H;         //Height

  int width = -1;
  int height = -1;

  //---------------------------
};

}
