#ifndef STRUCT_SWARM_H
#define STRUCT_SWARM_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_config.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

#include <k4a/k4a.hpp>


struct Struct_k4a_swarm{
  //---------------------------

  K4A_device* selected_device = nullptr;
  std::vector<K4A_device*> vec_device;

  //---------------------------
};



#endif
