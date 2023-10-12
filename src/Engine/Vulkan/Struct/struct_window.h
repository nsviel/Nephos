#ifndef STRUCT_WINDOW_H
#define STRUCT_WINDOW_H

#include <Specific/common.h>
#include <Window/Window.h>


struct Struct_window{
  //---------------------------

  bool is_resized = false;
  Window* windowManager;

  VkExtent2D extent;
  VkSurfaceKHR surface;

  //---------------------------
};


#endif
