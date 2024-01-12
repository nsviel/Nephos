#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <k4arecord/playback.hpp>


namespace k4n::config{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

public:
  //Capture configuration
  void make_device_configuration(k4n::Device* k4n_device);
  void find_playback_configuration(k4n::Device* k4n_device);

  //Playback configuration
  void find_config_fps(k4n::Device* k4n_device, k4a_record_configuration_t& configuration);
  void find_config_synchro(k4n::Device* k4n_device, k4a_record_configuration_t& configuration);
  void find_config_depth(k4n::Device* k4n_device, k4a_record_configuration_t& configuration);
  void find_config_color(k4n::Device* k4n_device, k4a_record_configuration_t& configuration);
  void find_config_format(k4n::Device* k4n_device, k4a_record_configuration_t& configuration);
  void find_config_device(k4n::Device* k4n_device, k4a_record_configuration_t& configuration);

private:

};

}
