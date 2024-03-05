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
  void make_sensor_configuration_initial(k4n::dev::Sensor* k4n_sensor);
  void find_playback_configuration(k4n::dev::Sensor* k4n_sensor);

  //Playback configuration
  void find_config_fps(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_synchro(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_depth(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_color(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_format(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_device(k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);

private:

};

}
