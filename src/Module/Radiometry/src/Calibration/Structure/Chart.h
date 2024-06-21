#pragma once

#include <Utility/Base/Type/Path.h>
#include <string>
#include <vector>


namespace rad::calibration::structure{

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
