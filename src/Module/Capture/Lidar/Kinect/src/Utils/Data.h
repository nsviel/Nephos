#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Device;}


namespace k4n::utils{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //IR function
  void convert_ir_into_color(k4n::dev::Device* sensor, std::vector<uint8_t>& output);
  void find_ir_level(k4n::dev::Device* sensor);

  //Depth function
  void convert_depth_into_color(k4n::dev::Device* sensor, std::vector<uint8_t>& output);
  void find_depth_mode_range(k4n::dev::Device* sensor);

private:

};

}
