#ifndef VK_PARAM_H
#define VK_PARAM_H

#include "VK_struct/Struct_window.h"
#include "VK_struct/Struct_instance.h"
#include "VK_struct/Struct_device.h"
#include "VK_struct/Struct_swapchain.h"
#include "VK_struct/Struct_renderpass.h"
#include "VK_struct/Struct_info.h"
#include "VK_struct/Struct_data.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Struct_vulkan{
  //---------------------------

  //Element
  int nb_frame;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  VkCommandPool command_pool;
  VkDescriptorPool descriptor_pool;
  VkViewport viewport;
  VkRect2D scissor;

  //Structure
  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;
  Struct_info info;
  Struct_data canvas;

  //Data
  std::vector<Struct_renderpass*> vec_renderpass;
  std::vector<Struct_image*> vec_texture;
  std::list<Struct_data*> list_data_scene;
  std::list<Struct_data*> list_data_glyph;

  //---------------------------
};

#endif
