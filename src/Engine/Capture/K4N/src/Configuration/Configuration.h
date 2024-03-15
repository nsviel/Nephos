#pragma once

#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>

namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Master;}


namespace k4n::config{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

public:
  //Capture configuration
  void make_master_configuration_initial(k4n::dev::Master* master);
  void make_sensor_configuration(k4n::dev::Sensor* k4n_sensor);
  void make_sensor_color_configuration(k4n::dev::Sensor* sensor);

  //Playback configuration
  void find_playback_configuration(k4n::dev::Sensor* k4n_sensor);

  //Playback configuration
  string find_mode_fps(int mode);
  string find_mode_synchro(int mode);
  string find_mode_depth(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  string find_mode_color(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  string find_mode_format(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  string find_mode_device(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);

private:

};

}
