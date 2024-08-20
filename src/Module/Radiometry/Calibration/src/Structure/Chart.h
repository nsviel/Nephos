#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>
#include <vector>


namespace rad::cal::structure{

struct Chart{
  //---------------------------

  Chart(){
    path.insert("../media/calibration/chart.data");
  }

  //General
  std::string mode = "NFOV";
  utl::base::Path path;

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //---------------------------
};

}
