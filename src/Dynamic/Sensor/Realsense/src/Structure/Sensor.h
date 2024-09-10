#pragma once

#include <Realsense/src/Structure/Device.h>
#include <Data/Namespace.h>
#include <string>


namespace rlx::base{

struct Sensor : public dat::base::Sensor{
  //---------------------------

  rlx::base::Device device;

  //---------------------------
};

}
