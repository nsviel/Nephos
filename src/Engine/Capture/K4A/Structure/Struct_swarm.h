#pragma once

#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <list>

class K4A_device;


namespace eng::kinect::structure{

struct Swarm{
  //---------------------------

  K4A_device* selected_device = nullptr;
  std::list<K4A_device*> list_device;
  int nb_device = 0;
  int nb_capture = 0;
  int nb_playback = 0;

  //---------------------------
};

}
