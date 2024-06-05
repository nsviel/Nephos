#pragma once

#include <Utility/Specific/Common.h>
#include <k4arecord/playback.hpp>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::dev{class Sensor;}
namespace k4n::playback{class Sensor;}
namespace k4n::dev{class Master;}
namespace dat::base{class Set;}


namespace k4n::utils{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(k4n::Node* node_k4n);
  ~Configuration();

public:
  //Configuration function
  void make_default_configuration();
  void make_sensor_configuration(k4n::structure::Sensor* k4n_sensor);
  void make_sensor_color_configuration(k4n::structure::Sensor* sensor);
  void find_playback_configuration(k4n::playback::Sensor* k4n_sensor);
  void reset_color_configuration(k4n::structure::Sensor* k4n_sensor);

  //Calibration function
  void make_transformation_from_calibration(k4n::structure::Sensor* sensor);
  void make_capture_calibration(k4n::structure::Sensor* sensor);
  void find_playback_calibration(k4n::playback::Sensor* sensor);

  //Playback configuration
  string find_mode_fps(int mode);
  string find_mode_synchro(int mode);
  string find_mode_depth(int mode);
  string find_mode_color_resolution(int mode);
  string find_mode_color_format(int mode);

private:
  k4n::Structure* k4n_struct;
};

}
