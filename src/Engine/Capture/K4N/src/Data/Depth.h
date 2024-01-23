#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>


namespace eng::k4n::data{

class Depth
{
public:
  //Constructor / Destructor
  Depth();
  ~Depth();

public:
  //Main function
  std::vector<uint8_t> convert_depth_into_color(eng::k4n::dev::Sensor* device);
  void find_depth_mode_range(eng::k4n::dev::Sensor* device);

private:
};

}
