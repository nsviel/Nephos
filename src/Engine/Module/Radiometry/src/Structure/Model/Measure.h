#pragma once

#include <string>
#include <vector>


namespace radio::structure{

struct Measure{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration/measure.data";
  std::vector<glm::vec3> vec_data;
  utl::type::Plot IfR;
  utl::type::Plot IfIt;
  utl::type::Plot IfRIt;

  //---------------------------
};

}
