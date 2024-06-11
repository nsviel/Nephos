#pragma once

#include <string>
#include <vector>


namespace rad::model::chart::structure{

struct Chart{
  //---------------------------

  std::string get_current_path(){
    std::string path = dir+ "/" + mode + "_" + filename;
    return path;
  }

  //General
  std::string mode = "NFOV";
  std::string filename = "chart.data";
  std::string dir = "../media/calibration";

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //---------------------------
};

}
