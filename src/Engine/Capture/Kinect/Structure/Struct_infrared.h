#pragma once


namespace eng::kinect::structure{

struct Infrared_config{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //---------------------------

  eng::kinect::structure::Infrared_config config;
  eng::kinect::structure::Image image;

  //---------------------------
};

}
