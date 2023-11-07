#ifndef STRUCT_WINDOW_H
#define STRUCT_WINDOW_H

#include <ELE_specific/common.h>
#include <ELE_window/ELE_window.h>


struct Struct_window{
  //---------------------------

  bool is_resized = false;
  ELE_window* ele_window;

  VkExtent2D extent;
  VkSurfaceKHR surface;

  //---------------------------
};


#endif
