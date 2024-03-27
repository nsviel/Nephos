#pragma once

#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Window{
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
