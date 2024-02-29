#pragma once

#include <Engine/Capture/K4N/src/Device/Sensor.h>
#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>


namespace k4n::config{

class USB
{
public:
  //Constructor / Destructor
  USB();
  ~USB();

public:
  //Main function
  void reset_usb_port(string filename);
  
private:

};

}
