#pragma once

#include <Utility/Specific/common.h>
#include <K4N/Namespace.h>

namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}


namespace k4n::structure{

enum Mode{
  CAMERA = 0,
  UNICOLOR = 1,
  INTENSITY = 2,
  HEATMAP = 3,
  STRUCTURE = 4,
};


struct Struct_k4n{
  //General scene structure
  //---------------------------

  Struct_k4n(k4n::Node* node_k4n){
    this->node_engine = node_k4n->get_node_engine();
    this->node_scene = node_k4n->get_node_scene();
    this->node_profiler = node_k4n->get_node_profiler();
  }

  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  int UID = 0;
  int nb_connected_sensor = 0;
  bool connected_device_change = false;
  k4n::dev::Master* selected_master = nullptr;
  std::list<k4n::dev::Master*> list_master;
  std::list<k4n::dev::Sensor*> list_sensor;

  //---------------------------
};

}
