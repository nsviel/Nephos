#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Device/Namespace.h>
#include <k4arecord/playback.hpp>


namespace k4n::config{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration();
  ~Configuration();

public:
  //Main function
  void init_playback_calibration(k4n::truc::K4A_device* k4a_device);
  void init_device_calibration(k4n::truc::K4A_device* k4a_device);
  void init_device_transformation(k4n::truc::K4A_device* k4a_device);
  void make_k4a_configuration(k4n::truc::K4A_device* k4a_device);
  void find_file_information(k4n::truc::K4A_device* k4a_device);

  //Subfunction
  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

private:

};

}
