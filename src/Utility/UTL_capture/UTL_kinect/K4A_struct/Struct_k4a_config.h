#ifndef STRUCT_K4A_CONFIG_H
#define STRUCT_K4A_CONFIG_H

#include <k4a/k4a.hpp>

#define VENDOR_MICROSOFT 0x045E
#define ID_RGB 0x097D
#define ID_DEPTH 0x097C


struct Struct_k4a_config{
  //---------------------------

  bool disable_streaming_indicator = false;
  bool synchronized_images_only = true;

  k4a_fps_t fps = K4A_FRAMES_PER_SECOND_30;
  k4a_wired_sync_mode_t wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
  k4a_device_configuration_t k4a_config;

  uint32_t subordinate_delay_off_master_usec = 0;
  int32_t depth_delay_off_color_usec = 0;

  //---------------------------
};



#endif
