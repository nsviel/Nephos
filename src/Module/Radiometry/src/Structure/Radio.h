#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Radiometry/src/Structure/Detection/Detection.h>

namespace rad{

struct Structure{
  //---------------------------

  //Constructor
  Structure(rad::Node* node_radio){
    this->node_engine = node_radio->get_node_engine();
    this->node_scene = node_radio->get_node_scene();
    this->node_profiler = node_radio->get_node_profiler();
  }

  //Dependancies
  eng::Node* node_engine;
  sce::Node* node_scene;
  prf::Node* node_profiler;

  bool panel_open = false;
  string state = "Wait validation";

  //Structure
  rad::structure::Detection detection;
  rad::structure::Model model;

  //---------------------------
};

}
