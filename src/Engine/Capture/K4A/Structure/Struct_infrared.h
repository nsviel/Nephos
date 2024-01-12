#pragma once


namespace k4a::stucture{

struct Infrared_config{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //---------------------------

  k4a::stucture::Infrared_config config;
  k4a::stucture::Image image;

  //---------------------------
};

}
