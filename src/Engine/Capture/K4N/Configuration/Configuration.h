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
  //Device function
  void make_device_transformation(k4n::Device* k4n_device);
  void make_device_configuration(k4n::Device* k4n_device);

  //Capture function
  void make_capture_calibration(k4n::Device* k4n_device);

  //Playback function
  void find_playback_calibration(k4n::Device* k4n_device);
  void find_playback_configuration(k4n::Device* k4n_device);
  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

private:

};

}
