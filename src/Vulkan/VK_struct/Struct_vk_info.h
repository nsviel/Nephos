#ifndef STRUCT_VK_TIME_H
#define STRUCT_VK_TIME_H

#include <VK_struct/Struct_vk_physical_device.h>
#include <UTL_specific/common.h>


struct Struct_vk_info{
  //---------------------------

  float engine_init;
  float engine_fps;

  vector<float> draw_frame;
  vector<float> time_rp_scene;
  vector<float> time_rp_edl;
  vector<float> time_rp_gui;

  //---------------------------
};


#endif
