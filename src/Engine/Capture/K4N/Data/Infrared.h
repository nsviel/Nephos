#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>


namespace k4n::data{

class Infrared
{
public:
  //Constructor / Destructor
  Infrared();
  ~Infrared();

public:
  //Main function
  std::vector<uint8_t> convert_ir_into_color(k4n::Device* device);
  void find_ir_level(k4n::Device* device);

private:

};

}
