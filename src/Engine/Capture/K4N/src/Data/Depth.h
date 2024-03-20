#pragma once

#include <Utility/Specific/common.h>

namespace k4n::dev{class Sensor;}


namespace k4n::data{

class Depth
{
public:
  //Constructor / Destructor
  Depth();
  ~Depth();

public:
  //Main function
  void convert_depth_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output);
  void convert_depth_into_color_(k4n::dev::Sensor* sensor);
  void find_depth_mode_range(k4n::dev::Sensor* sensor);

private:
};

}
