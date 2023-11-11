#ifndef STRUCT_ENTITY_H
#define STRUCT_ENTITY_H

#include <VK_struct/typedef.h>
#include <VK_struct/Struct_binding.h>
#include <VK_struct/Struct_image.h>

#include <ELE_specific/common.h>


struct Struct_buffer{
  //---------------------------

  VkBuffer vbo = VK_NULL_HANDLE;
  VkDeviceMemory mem;

  //---------------------------
};

struct Struct_entity{
  //---------------------------

  Object* object;

  //Data
  bool has_xyz = false;
  bool has_rgb = false;
  bool has_uv = false;

  //Buffer
  Struct_buffer xyz;
  Struct_buffer rgb;
  Struct_buffer uv;

  //Binding
  list<Struct_image*> list_texture;
  VkCommandBuffer command_buffer_secondary;
  Struct_binding binding;

  //---------------------------
};

#endif
