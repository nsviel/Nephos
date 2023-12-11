#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/VK_typedef.h>
#include <VK_struct/Struct_vk_binding.h>
#include <VK_struct/Image.h>

#include <UTL_specific/common.h>


namespace vk::structure{

struct Entity{
  //---------------------------

  data::Object* object;

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
  Struct_vk_binding binding;

  //---------------------------
};

}
