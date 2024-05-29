#pragma once

#include <string>
#include <vector>


namespace rad::model::structure{

struct Chart{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration/chart.data";

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //---------------------------
};

}
