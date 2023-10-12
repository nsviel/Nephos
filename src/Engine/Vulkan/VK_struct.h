#ifndef VK_PARAM_H
#define VK_PARAM_H

#include "Struct/struct_window.h"
#include "Struct/struct_instance.h"
#include "Struct/struct_device.h"
#include "Struct/struct_swapchain.h"
#include "Struct/struct_renderpass.h"
#include "Struct/struct_time.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct VK_struct{
  //---------------------------

  int nb_frame;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  VkCommandPool command_pool;

  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;
  Struct_time time;

  Struct_renderpass renderpass_scene;
  Struct_renderpass renderpass_edl;
  Struct_renderpass renderpass_psr;
  Struct_renderpass renderpass_ui;

  //---------------------------
};

#endif
