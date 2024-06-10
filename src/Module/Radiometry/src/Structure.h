#pragma once

#include <Radiometry/src/Detection/Sphere/Structure/Structure.h>
#include <Radiometry/src/Model/Structure.h>
#include <Radiometry/src/Correction/Structure.h>
#include <string>


namespace rad{

struct Structure{
  //---------------------------

  bool panel_open = false;
  std::string state = "Wait validation";

  //Structure
  rad::detection::sphere::Structure detection;
  rad::model::Structure model;
  rad::correction::Structure correction;

  //---------------------------
};

}
