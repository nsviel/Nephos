#pragma once

#include <UTL_specific/common.h>


namespace vk::structure{

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

}
