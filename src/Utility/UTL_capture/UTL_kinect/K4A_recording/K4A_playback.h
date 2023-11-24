#ifndef K4A_PLAYBACK__H
#define K4A_PLAYBACK__H

#include <UTL_specific/common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_info.h>

class Struct_kinect;
class K4A_device;


class K4A_playback
{
public:
  //Constructor / Destructor
  K4A_playback(Struct_kinect* struct_kinect);
  ~K4A_playback();

public:
  //Main function
  void find_file_information(string path);
  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

  inline Struct_k4a_info& get_struct_record(){return struct_info;}

private:
  K4A_device* k4a_device;
  Struct_kinect* struct_kinect;
  Struct_k4a_info struct_info;
};

#endif
