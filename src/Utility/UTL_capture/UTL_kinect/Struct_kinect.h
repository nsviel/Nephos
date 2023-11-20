#ifndef STRUCT_KINECT_H
#define STRUCT_KINECT_H

#include "K4A_struct/Struct_k4a_config.h"
#include "K4A_struct/Struct_k4a_device.h"

#include <k4a/k4a.hpp>


struct Struct_kinect{
  //---------------------------

  Struct_k4a_config config;
  Struct_k4a_device* selected_device = nullptr;
  std::vector<Struct_k4a_device> vec_device;

  //---------------------------
};



#endif
