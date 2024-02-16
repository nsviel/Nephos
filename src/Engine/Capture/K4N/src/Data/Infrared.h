#pragma once

#include <Utility/Specific/common.h>

namespace k4n::dev{class Sensor;}


namespace k4n::data{

class Infrared
{
public:
  //Constructor / Destructor
  Infrared();
  ~Infrared();

public:
  //Main function
  std::vector<uint8_t> convert_ir_into_color(k4n::dev::Sensor* sensor);
  void find_ir_level(k4n::dev::Sensor* sensor);

private:

};

}
