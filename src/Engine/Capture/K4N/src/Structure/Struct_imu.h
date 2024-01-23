#pragma once


namespace eng::k4n::structure{

struct IMU_config{
  //---------------------------

  bool enabled = true;

  //---------------------------
};

struct IMU{
  //---------------------------

  eng::k4n::structure::IMU_config config;

  //---------------------------
};

}
