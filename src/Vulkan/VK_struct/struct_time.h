#ifndef STRUCT_TIME_H
#define STRUCT_TIME_H

#include <ELE_specific/common.h>


struct Struct_time{
  //---------------------------

  float engine_init;
  float engine_fps;

  vector<float> draw_frame;
  vector<float> renderpass_scene;
  vector<float> renderpass_edl;
  vector<float> renderpass_ui;

  //---------------------------
};


#endif
