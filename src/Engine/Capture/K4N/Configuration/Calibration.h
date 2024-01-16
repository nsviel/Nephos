#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <k4arecord/playback.hpp>


namespace k4n::config{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration();
  ~Calibration();

public:
  //Main function
  void make_device_transformation(k4n::Sensor* k4n_sensor);
  void make_capture_calibration(k4n::Sensor* k4n_sensor);
  void find_playback_calibration(k4n::Sensor* k4n_sensor);

private:

};

}
