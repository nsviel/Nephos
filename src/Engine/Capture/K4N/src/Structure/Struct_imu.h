#pragma once


namespace k4n::src::str{

struct IMU_config{
  //---------------------------

  bool enabled = true;

  //---------------------------
};

struct IMU{
  //---------------------------

  k4n::src::str::IMU_config config;

  //---------------------------
};

}
