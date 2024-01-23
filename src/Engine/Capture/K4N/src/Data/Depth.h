#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>


namespace k4n::src::data{

class Depth
{
public:
  //Constructor / Destructor
  Depth();
  ~Depth();

public:
  //Main function
  std::vector<uint8_t> convert_depth_into_color(k4n::src::dev::Sensor* device);
  void find_depth_mode_range(k4n::src::dev::Sensor* device);

private:
};

}
