#pragma once

#include <Utility/Specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <Utility/Capture/Kinect/K4A_struct/Namespace.h>

class K4A_device;


class K4A_configuration
{
public:
  //Constructor / Destructor
  K4A_configuration();
  ~K4A_configuration();

public:
  //Main function
  void make_k4a_configuration(K4A_device* device);
  void find_file_information(K4A_device* device, string path);

  //Subfunction
  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

  inline util::kinect::structure::Info& get_struct_record(){return struct_info;}

private:
  util::kinect::structure::Info struct_info;
};
