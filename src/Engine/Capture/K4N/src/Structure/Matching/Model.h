#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Model{
  //---------------------------

  std::string path = "";
  std::vector<glm::vec3> vec_data;
  int degree = 5;

  utl::type::Plot IfR;
  utl::type::Plot IfIt;
  utl::type::Plot IfRIt;

  //---------------------------
};

}
