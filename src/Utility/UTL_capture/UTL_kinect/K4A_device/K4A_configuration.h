#ifndef K4A_PLAYBACK__H
#define K4A_PLAYBACK__H

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>

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
  void find_file_information(string path);

  //Subfunction
  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

  inline Struct_k4a_info& get_struct_record(){return struct_info;}

private:
  Struct_k4a_info struct_info;
};

#endif
