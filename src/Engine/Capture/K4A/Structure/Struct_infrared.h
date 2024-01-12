#pragma once


namespace k4n::structure{

struct Infrared_config{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //---------------------------

  k4n::structure::Infrared_config config;
  k4n::structure::Image image;

  //---------------------------
};

}
