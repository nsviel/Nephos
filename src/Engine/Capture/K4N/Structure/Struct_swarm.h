#pragma once

#include <Engine/Capture/K4N/Device/K4A_device.h>
#include <list>


namespace k4n::structure{

struct Swarm{
  //---------------------------

  k4n::truc::K4A_device* selected_device = nullptr;
  std::list<k4n::truc::K4A_device*> list_device;

  int nb_device = 0;
  int nb_capture = 0;
  int nb_playback = 0;

  //---------------------------
};

}
