#pragma once

#include <Kinect/src/Structure/Sensor/Data.h>


namespace k4n::structure{

struct Infrared_config{
  //---------------------------

  bool enabled = true;

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //Structure for sensor infrared field
  //---------------------------

  k4n::structure::Infrared_config config;
  k4n::structure::Data data;
  k4n::structure::Data cloud;

  //---------------------------
};

}
