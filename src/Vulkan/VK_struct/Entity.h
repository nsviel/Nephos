#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/VK_typedef.h>
#include <Vulkan/VK_struct/Binding.h>
#include <Vulkan/VK_struct/Image.h>

#include <Utility/UTL_specific/common.h>


namespace vk::structure{

struct Entity{
  //---------------------------

  eng::structure::Object* object;

  //Data
  bool has_xyz = false;
  bool has_rgb = false;
  bool has_uv = false;

  //Buffer
  vk::structure::Buffer xyz;
  vk::structure::Buffer rgb;
  vk::structure::Buffer uv;

  //Binding
  list<Image*> list_texture;
  VkCommandBuffer command_buffer_secondary;
  vk::structure::Binding binding;

  //---------------------------
};

}
