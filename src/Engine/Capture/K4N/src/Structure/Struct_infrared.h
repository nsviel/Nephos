#pragma once


namespace k4n::src::str{

struct Infrared_config{
  //---------------------------

  bool enabled = true;
  
  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //---------------------------

  k4n::src::str::Infrared_config config;
  k4n::src::str::Image image;

  //---------------------------
};

}
