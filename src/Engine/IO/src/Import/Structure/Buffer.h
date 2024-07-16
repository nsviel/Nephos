#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace io::importer{

struct Buffer{
  //---------------------------

  std::vector<glm::vec3> xyz;  //Location
  std::vector<glm::vec3> Nxyz; //Normal
  std::vector<glm::vec3> rgb;  //Color
  std::vector<glm::vec4> rgba; //Displayed color
  std::vector<float> Is;       //Intensity
  std::vector<float> ts;       //Timestamp

  //---------------------------
};

}
