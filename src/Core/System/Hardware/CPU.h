#pragma once

#include <string>

namespace utl::hardware{

class CPU
{
public:
  //Constructor / Destructor
  CPU();
  ~CPU();

public:
  //Main function
  std::string get_name();
  float get_temperature();
  int get_temperature_max();
  int get_number_of_core();

private:

};

}
