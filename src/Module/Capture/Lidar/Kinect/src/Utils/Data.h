#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}


namespace k4n::utils{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //IR function
  void convert_ir_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output);
  void find_ir_level(k4n::dev::Sensor* sensor);

  //Depth function
  void convert_depth_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output);
  void convert_depth_into_color_(k4n::dev::Sensor* sensor);
  void find_depth_mode_range(k4n::dev::Sensor* sensor);

private:

};

}
