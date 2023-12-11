#pragma once

#include <Utility/UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <k4a/k4a.hpp>


struct Struct_k4a_swarm{
  //---------------------------

  K4A_device* selected_device = nullptr;
  std::list<K4A_device*> list_device;
  int nb_device_real;
  int nb_device_virtual;

  //---------------------------
};
