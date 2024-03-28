#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Model{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration.data";
  std::vector<glm::vec3> vec_data;
  float min_R = 1000;
  float max_R = -1;
  int degree = 5;

  //Plot stuff
  utl::type::Plot IfR;
  utl::type::Plot IfIt;
  utl::type::Plot IfRIt;

  //---------------------------
};

}
