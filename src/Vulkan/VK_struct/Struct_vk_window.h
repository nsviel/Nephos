#ifndef STRUCT_WINDOW_H
#define STRUCT_WINDOW_H

#include <UTL_specific/common.h>


struct Struct_vk_window{
  //---------------------------

  //Window stuff
  bool is_resized = false;
  GLFWwindow* glfw_window;
  vec2 window_dim;

  //Vulkan stuff
  VkExtent2D extent;
  VkSurfaceKHR surface;

  //---------------------------
};


#endif
