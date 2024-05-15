#pragma once


namespace k4n::imu{

struct Configuration{
  //---------------------------

  bool enabled = true;

  //---------------------------
};

struct Structure{
  //---------------------------

  k4n::imu::Configuration config;

  //---------------------------
};

}
