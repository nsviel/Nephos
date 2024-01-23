#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>


namespace eng::k4n::config{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration();
  ~Calibration();

public:
  //Main function
  void make_device_transformation(eng::k4n::dev::Sensor* k4n_sensor);
  void make_capture_calibration(eng::k4n::dev::Sensor* k4n_sensor);
  void find_playback_calibration(eng::k4n::dev::Sensor* k4n_sensor);

private:

};

}
