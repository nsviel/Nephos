#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Measure{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration_measure.data";
  std::vector<glm::vec3> vec_data;
  utl::type::Plot IfR;
  utl::type::Plot IfIt;
  utl::type::Plot IfRIt;

  //---------------------------
};

}
