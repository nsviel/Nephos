#pragma once

#include <nvml.h>


namespace sys::hardware{

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
  int get_temperature_max_slowdown();
  int get_temperature_max_shutdown();
  int get_temperature_max_gpu();
  int get_fan_speed();

private:
  nvmlDevice_t device;
};

}
