#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/src/Structure/Detection/Detection.h>

namespace rad{

struct Structure{
  //---------------------------

  bool panel_open = false;
  string state = "Wait validation";

  //Structure
  rad::structure::Detection detection;
  rad::structure::Model model;

  //---------------------------
};

}
