#pragma once

#include <Realsense/src/Structure/Device.h>
#include <Realsense/src/Structure/Image.h>
#include <Data/Namespace.h>


namespace rlx::base{

struct Sensor : public dat::base::Sensor{
  //---------------------------

  rlx::base::Device device;
  rlx::base::Image image;

  //---------------------------
};

}
