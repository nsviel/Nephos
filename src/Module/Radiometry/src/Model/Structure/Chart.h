#pragma once

#include <string>
#include <vector>


namespace rad::model::structure{

struct Chart{
  //---------------------------

  //General
  std::string path = "../media/record/calibration/chart.data";
  bool is_ready = false;

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //---------------------------
};

}
