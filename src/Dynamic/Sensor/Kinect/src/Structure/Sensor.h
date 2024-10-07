#pragma once

#include <Kinect/src/Structure/Device/Structure.h>
#include <Kinect/src/Structure/Configuration/Structure.h>
#include <Kinect/src/Structure/Data/Depth/Structure.h>
#include <Kinect/src/Structure/Data/Color/Structure.h>
#include <Kinect/src/Structure/Data/Infrared/Structure.h>
#include <Kinect/src/Structure/Data/IMU/Structure.h>
#include <Data/Base/Entity/Sensor.h>


namespace k4n::base{

struct Sensor : public dat::base::Sensor{
  //---------------------------

  //Device
  k4n::str::config::Structure config;
  k4n::str::device::Structure device;

  //Data
  k4n::str::color::Structure color;
  k4n::str::depth::Structure depth;
  k4n::str::infra::Structure infra;
  k4n::str::imu::Structure imu;

  //---------------------------
};

}
