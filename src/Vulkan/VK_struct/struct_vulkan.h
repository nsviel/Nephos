#ifndef VK_PARAM_H
#define VK_PARAM_H

#include "VK_struct/struct_window.h"
#include "VK_struct/struct_instance.h"
#include "VK_struct/struct_device.h"
#include "VK_struct/struct_swapchain.h"
#include "VK_struct/struct_renderpass.h"
#include "VK_struct/struct_time.h"
#include "VK_struct/struct_data.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Struct_vulkan{
  //---------------------------

  int nb_frame;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  VkCommandPool command_pool;
  VkDescriptorPool descriptor_pool;

  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;
  Struct_time time;
  Struct_data canvas;

  VkViewport viewport;
  VkRect2D scissor;

  Struct_renderpass renderpass_scene;
  Struct_renderpass renderpass_edl;
  Struct_renderpass renderpass_ui;
  std::vector<Struct_renderpass> vec_renderpass;
  std::vector<Struct_image*> vec_texture;

  std::list<Struct_data*> list_data_scene;
  std::list<Struct_data*> list_data_glyph;

  //---------------------------
};

#endif
