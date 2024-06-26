#pragma once


namespace utl::hardware{

class Nvidia
{
public:
  //Constructor / Destructor
  Nvidia();
  ~Nvidia();

public:
  //Main function
  float get_total_consumption();
  int get_temperature();
  int get_fan_speed();
  int get_power_usage();

  //Subfunction

private:

};

}
