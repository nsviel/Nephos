#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <list>


namespace k4n::structure{

struct Swarm{
  //---------------------------

  k4n::dev::Sensor* selected_device = nullptr;
  std::list<k4n::dev::Sensor*> list_sensor;

  //k4n::Master* selected_master = nullptr;
  //std::list<k4n::Master*> list_master;

  int nb_dev = 0;
  int nb_dev_capture = 0;
  int nb_dev_playback = 0;

  //---------------------------
};

}
