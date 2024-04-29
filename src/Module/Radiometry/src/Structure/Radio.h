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

  //Constructor
  Structure(rad::Node* node_radio){
    this->node_engine = node_radio->get_node_engine();
    this->node_data = node_radio->get_node_data();
    this->node_profiler = node_radio->get_node_profiler();
  }

  //Dependancies
  eng::Node* node_engine;
  dat::Node* node_data;
  prf::Node* node_profiler;

  bool panel_open = false;
  string state = "Wait validation";

  //Structure
  rad::structure::Detection detection;
  rad::structure::Model model;

  //---------------------------
};

}
