#pragma once

#include <k4a/k4a.hpp>
#include <cstdint>


namespace k4n::synchro{

struct Configuration{
  //---------------------------

  k4a_wired_sync_mode_t wired_mode = K4A_WIRED_SYNC_MODE_STANDALONE;

  uint32_t subordinate_delay_off_master_us = 0;
  uint32_t depth_delay_off_color_us = 0;
  uint32_t start_timestamp_offset_us = 0;

  bool disable_streaming_indicator = true;
  bool synchronized_images_only = true;

  //---------------------------
};

}
