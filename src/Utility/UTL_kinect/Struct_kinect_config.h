#ifndef STRUCT_KINECT_CONFIG_H
#define STRUCT_KINECT_CONFIG_H

#include <k4a/k4a.hpp>

#define VENDOR_MICROSOFT 0x045E
#define ID_RGB 0x097D
#define ID_DEPTH 0x097C


struct Struct_kinect_config{
  //---------------------------

  bool enable_camera_color = true;
  bool enable_camera_depth = true;
  bool disable_streaming_indicator = false;
  bool synchronized_images_only = true;

  k4a_image_format_t color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4a_color_resolution_t color_resolution = K4A_COLOR_RESOLUTION_720P;
  k4a_depth_mode_t depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  k4a_fps_t camera_fps = K4A_FRAMES_PER_SECOND_30;
  k4a_wired_sync_mode_t wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
  k4a_device_configuration_t k4a_config;

  uint32_t subordinate_delay_off_master_usec = 0;
  int32_t depth_delay_off_color_usec = 0;

  //---------------------------
};



#endif
