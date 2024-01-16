#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/VK_typedef.h>

#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Object{
  //---------------------------

  entity::Object* object;

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
