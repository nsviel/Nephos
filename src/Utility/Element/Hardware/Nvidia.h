#pragma once

#include <nvml.h>


namespace utl::hardware{

class Nvidia
{
public:
  //Constructor / Destructor
  Nvidia();
  ~Nvidia();

public:
  //Main function
  void init();

  //Subfunction
  float get_total_consumption();
  float get_power_usage();
  int get_temperature();
  int get_fan_speed();

private:
  nvmlDevice_t device;
};

}
