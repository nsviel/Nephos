#ifndef STRUCT_KINECT_H
#define STRUCT_KINECT_H

#include "K4A_struct/Struct_k4a_config.h"
#include "K4A_device/K4A_device.h"

#include <k4a/k4a.hpp>


struct Struct_kinect{
  //---------------------------

  K4A_device* selected_device = nullptr;
  std::vector<K4A_device> vec_device;

  //---------------------------
};



#endif
