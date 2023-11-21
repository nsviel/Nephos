#ifndef STRUCT_VK_ENTITY_H
#define STRUCT_VK_ENTITY_H

#include <VK_struct/VK_typedef.h>
#include <VK_struct/Struct_vk_binding.h>
#include <VK_struct/Struct_vk_image.h>
#include <VK_struct/Struct_vk_buffer.h>
#include <UTL_specific/common.h>


struct Struct_vk_entity{
  //---------------------------

  Object* object;

  //Data
  bool has_xyz = false;
  bool has_rgb = false;
  bool has_uv = false;

  //Buffer
  Struct_vk_buffer xyz;
  Struct_vk_buffer rgb;
  Struct_vk_buffer uv;

  //Binding
  list<Struct_vk_image*> list_texture;
  VkCommandBuffer command_buffer_secondary;
  Struct_vk_binding binding;

  //---------------------------
};

#endif
