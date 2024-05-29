#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/src/Detection/Structure/Structure.h>
#include <Radiometry/src/Model/Structure/Model.h>

namespace rad{

struct Structure{
  //---------------------------

  bool panel_open = false;
  string state = "Wait validation";

  //Structure
  rad::detection::Structure detection;
  rad::structure::Model model;
  rad::structure::Correction correction;

  //---------------------------
};

}
