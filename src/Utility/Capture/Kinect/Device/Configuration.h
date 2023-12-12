#pragma once

#include <Utility/Capture/Kinect/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Capture/Kinect/Device/K4A_device.h>
#include <k4arecord/playback.hpp>

class K4A_device;


namespace util::kinect::configuration{

  //Main function
  void init_device_transformation(K4A_device* k4a_device);
  void make_k4a_configuration(K4A_device* k4a_device);
  void find_file_information(K4A_device* k4a_device, string path);

  //Subfunction
  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

}
