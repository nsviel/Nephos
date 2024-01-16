#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <list>


namespace k4n::structure{

struct Swarm{
  //---------------------------

  k4n::Sensor* selected_device = nullptr;
  std::list<k4n::Sensor*> list_device;

  //k4n::Master* selected_master = nullptr;
  //std::list<k4n::Master*> list_master;

  int nb_device = 0;
  int nb_capture = 0;
  int nb_playback = 0;

  //---------------------------
};

}
