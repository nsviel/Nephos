#pragma once

#include <Engine/Capture/K4N/Device/Device.h>
#include <list>


namespace k4n::structure{

struct Swarm{
  //---------------------------

  k4n::device::Device* selected_device = nullptr;
  std::list<k4n::device::Device*> list_device;

  int nb_device = 0;
  int nb_capture = 0;
  int nb_playback = 0;

  //---------------------------
};

}
