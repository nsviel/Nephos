#pragma once


namespace util::kinect::structure{

struct Infrared_config{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //---------------------------

  util::kinect::structure::Infrared_config config;
  util::kinect::structure::Image image;

  //---------------------------
};

}
