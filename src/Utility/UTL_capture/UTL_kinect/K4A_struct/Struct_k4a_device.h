#ifndef STRUCT_K4A_DEVICE_H
#define STRUCT_K4A_DEVICE_H

#include "Struct_k4a_config.h"

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_device{
  //---------------------------

  int index;
  std::string serial_number;
  Struct_k4a_config config;

  //---------------------------
};



#endif
