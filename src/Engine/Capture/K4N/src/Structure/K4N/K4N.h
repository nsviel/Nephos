#pragma once

#include <K4N/src/Structure/K4N/Device.h>
#include <K4N/src/Structure/Calibration/Calibration.h>
#include <Utility/Specific/common.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::structure{

enum Mode{
  CAMERA = 0,
  UNICOLOR = 1,
  INTENSITY = 2,
  HEATMAP = 3,
  STRUCTURE = 4,
};


struct K4N{
  //General scene structure
  //---------------------------

  //Constructor
  K4N(k4n::Node* node_k4n){
    this->node_engine = node_k4n->get_node_engine();
    this->node_scene = node_k4n->get_node_scene();
    this->node_profiler = node_k4n->get_node_profiler();
  }

  //Dependancies
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  //Structure
  k4n::structure::Device device;
  k4n::structure::Calibration calibration;

  //---------------------------
};

}
