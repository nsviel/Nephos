#pragma once

#include <Engine/Capture/K4N/src/Device/Sensor.h>
#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>


namespace eng::k4n::config{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

public:
  //Capture configuration
  void make_device_configuration(eng::k4n::dev::Sensor* k4n_sensor);
  void find_playback_configuration(eng::k4n::dev::Sensor* k4n_sensor);

  //Playback configuration
  void find_config_fps(eng::k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_synchro(eng::k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_depth(eng::k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_color(eng::k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_format(eng::k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);
  void find_config_device(eng::k4n::dev::Sensor* k4n_sensor, k4a_record_configuration_t& configuration);

private:

};

}
