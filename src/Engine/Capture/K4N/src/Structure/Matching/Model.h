#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Model{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration.data";
  std::vector<glm::vec3> vec_data;
  utl::type::Axis x;
  utl::type::Axis y;
  int degree = 5;

  //Plot stuff
  utl::type::Plot IfR;
  utl::type::Plot IfIt;
  utl::type::Plot IfRIt;

  //---------------------------
};

}
