#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n::dev{class Sensor;}


namespace eng::k4n::data{

class Infrared
{
public:
  //Constructor / Destructor
  Infrared();
  ~Infrared();

public:
  //Main function
  std::vector<uint8_t> convert_ir_into_color(eng::k4n::dev::Sensor* sensor);
  void find_ir_level(eng::k4n::dev::Sensor* sensor);

private:

};

}
