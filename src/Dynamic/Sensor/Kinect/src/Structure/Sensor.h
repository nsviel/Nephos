#pragma once

#include <Kinect/src/Structure/Namespace.h>
#include <Kinect/src/Structure/Data/Depth/Structure.h>
#include <Kinect/src/Structure/Data/Color/Structure.h>
#include <Kinect/src/Structure/Data/Infrared/Structure.h>
#include <Data/Namespace.h>
#include <string>


namespace k4n::base{

struct Sensor : public dat::base::Sensor{
  //---------------------------

  //Data
  k4n::structure::Setting setting;
  k4n::str::color::Structure color;
  k4n::str::depth::Structure depth;
  k4n::str::infra::Structure infra;
  k4n::imu::Structure imu;
  k4n::structure::Cloud cloud;
  k4n::structure::Configuration config;

  //Device
  k4n::device::Structure device;
  k4n::firmware::Structure firmware;
  k4n::structure::FPS fps;

  std::string type_sensor = "";

  //---------------------------
};

}
