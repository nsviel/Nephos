#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>


namespace k4n::src::config{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

public:
  //Capture configuration
  void make_device_configuration(k4n::src::dev::Sensor* k4n_sensor);
  void find_playback_configuration(k4n::src::dev::Sensor* k4n_sensor);

  //Playback configuration
  void find_config_fps(k4n::src::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_synchro(k4n::src::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_depth(k4n::src::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_color(k4n::src::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_format(k4n::src::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_device(k4n::src::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);

private:

};

}
