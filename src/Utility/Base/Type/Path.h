#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace utl::base{

struct Path{
  //---------------------------

  std::string directory = "";
  std::string data = "";
  std::string transformation = "";
  std::string texture = "";

  //---------------------------
};

}
