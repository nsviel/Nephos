#pragma once

#include <string>
#include <vector>


namespace rad::model::structure{

struct Chart{
  //---------------------------

  //General
  std::string path = "../media/record/calibration/chart.data";
  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //---------------------------
};

}
