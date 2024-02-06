#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n::dev{class Sensor;}


namespace eng::k4n::data{

class Depth
{
public:
  //Constructor / Destructor
  Depth();
  ~Depth();

public:
  //Main function
  std::vector<uint8_t> convert_depth_into_color(eng::k4n::dev::Sensor* sensor);
  void convert_depth_into_color_(eng::k4n::dev::Sensor* sensor);
  void find_depth_mode_range(eng::k4n::dev::Sensor* sensor);

private:
};

}
