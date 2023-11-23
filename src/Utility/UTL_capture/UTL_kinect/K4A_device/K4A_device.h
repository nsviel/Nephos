#ifndef K4A_DEVICE_H
#define K4A_DEVICE_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>

#include <UTL_specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Struct_kinect;


class K4A_device
{
public:
  //Constructor / Destructor
  K4A_device(Struct_kinect* struct_kinect);
  ~K4A_device();

public:
  //Main function
  void refresh_device_list();

  string find_name_from_config(k4a_wired_sync_mode_t& value);
  string find_name_from_config(k4a_fps_t& value);
  string find_name_from_config(k4a_depth_mode_t& value);
  string find_name_from_config(k4a_color_resolution_t& value);
  string find_name_from_config(k4a_image_format_t& value);

private:
  Struct_kinect* struct_kinect;
};

#endif
