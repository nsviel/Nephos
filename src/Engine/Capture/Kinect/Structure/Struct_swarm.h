#pragma once

#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <list>

class K4A_device;


namespace eng::kinect::structure{

struct Swarm{
  //---------------------------

  K4A_device* selected_device = nullptr;
  std::list<K4A_device*> list_device;
  int nb_device;
  int nb_playback;

  //---------------------------
};

}
