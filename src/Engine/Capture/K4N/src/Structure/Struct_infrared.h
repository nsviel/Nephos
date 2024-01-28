#pragma once


namespace eng::k4n::structure{

struct Infrared_config{
  //---------------------------

  bool enabled = true;

  uint16_t level_min = 0;
  uint16_t level_max = 1000;

  //---------------------------
};

struct Infrared{
  //---------------------------

  eng::k4n::structure::Infrared_config config;
  eng::k4n::structure::Data data;
  eng::k4n::structure::Data data_to_color;
  
  //---------------------------
};

}
