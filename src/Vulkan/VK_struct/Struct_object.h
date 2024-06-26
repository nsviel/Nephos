#pragma once

#include <Vulkan/VK_struct/VK_typedef.h>
#include <Vulkan/VK_struct/Struct_buffer.h>
#include <Vulkan/VK_struct/Struct_texture.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <list>


namespace vk::structure{

struct Buffers{
  //---------------------------

  vk::structure::Buffer xyz;
  vk::structure::Buffer xyz_stagger;
  vk::structure::Buffer rgba;
  vk::structure::Buffer rgba_stagger;
  vk::structure::Buffer uv;
  vk::structure::Buffer uv_stagger;

  //---------------------------
};

struct Object{
  //---------------------------

  int UID = 0;

  utl::base::Data* data = nullptr;
  utl::base::Pose* pose = nullptr;

  //Data
  bool has_xyz = false;
  bool has_rgba = false;
  bool has_uv = false;

  //Buffer
  vk::structure::Buffers buffer;

  //Binding
  std::list<vk::structure::Texture*> list_vk_texture;
  VkCommandBuffer command_buffer_secondary = VK_NULL_HANDLE;
  vk::binding::structure::Binding binding;

  //---------------------------
};

}
