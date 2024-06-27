#pragma once

#include <Vulkan/VK_data/Structure/Buffer.h>
#include <Vulkan/VK_image/Structure/Texture.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <list>


namespace vk::structure{

struct Buffers{
  //---------------------------

  vk::data::structure::Buffer xyz;
  vk::data::structure::Buffer xyz_stagger;
  vk::data::structure::Buffer rgba;
  vk::data::structure::Buffer rgba_stagger;
  vk::data::structure::Buffer uv;
  vk::data::structure::Buffer uv_stagger;

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
