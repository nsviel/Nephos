#pragma once


namespace util::kinect::structure{

struct Synchro{
  //---------------------------

  uint32_t subordinate_delay_off_master_us = 0;
  int32_t depth_delay_off_color_us = 0;
  bool disable_streaming_indicator = false;
  bool synchronized_images_only = true;

  //---------------------------
};

}
