#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Graph/Namespace.h>
#include <Radiometry/src/Structure/Detection/Detection.h>

namespace radio{

struct Structure{
  //---------------------------

  //Constructor
  Structure(radio::Node* node_radio){
    this->node_engine = node_radio->get_node_engine();
    this->node_scene = node_radio->get_node_scene();
    this->node_profiler = node_radio->get_node_profiler();
  }

  //Dependancies
  eng::Node* node_engine;
  scene::Node* node_scene;
  prf::Node* node_profiler;

  bool panel_open = false;
  string state = "Wait validation";

  //Structure
  radio::structure::Detection detection;
  radio::structure::Model model;

  //---------------------------
};

}
