#pragma once

#include <Realsense/src/Structure/Device.h>
#include <Data/Namespace.h>
#include <librealsense2/rs.hpp>
#include <string>


namespace rlx::base{

struct Sensor : public dat::base::Sensor{
  //---------------------------

  rlx::base::Device device;
  rs2::frameset frameset;

  //---------------------------
};

}
