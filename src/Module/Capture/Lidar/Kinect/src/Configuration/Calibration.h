#pragma once

#include <Kinect/Namespace.h>
#include <Utility/Specific/Common.h>
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
  void make_transformation_from_calibration(k4n::dev::Sensor* sensor);
  void make_capture_calibration(k4n::dev::Sensor* sensor);
  void find_playback_calibration(k4n::dev::Sensor* sensor);

private:

};

}
