#pragma once


namespace k4n::structure{

struct IMU_config{
  //---------------------------

  bool enabled = true;

  //---------------------------
};

struct IMU{
  //---------------------------

  k4n::structure::IMU_config config;

  //---------------------------
};

}
