#pragma once

#include <Vulkan/VK_data/Structure/Buffer.h>
#include <Vulkan/VK_image/Structure/Texture.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <memory>
#include <list>


namespace vk::structure{

struct Buffering{
  //---------------------------

  vk::data::structure::Buffer data;
  vk::data::structure::Buffer stagger;

  //---------------------------
};

struct Buffer_set{
  //---------------------------

  vk::structure::Buffering xyz;
  vk::structure::Buffering rgba;
  vk::structure::Buffering uv;

  //---------------------------
};

struct Object{
  //---------------------------

  //Data
  int UID = 0;
  bool has_xyz = false;
  bool has_rgba = false;
  bool has_uv = false;
  std::shared_ptr<utl::base::Data> data = std::make_shared<utl::base::Data>();
  std::shared_ptr<utl::base::Pose> pose = std::make_shared<utl::base::Pose>();
  
  //Binding
  std::list< std::shared_ptr<vk::structure::Texture> > list_vk_texture;
  VkCommandBuffer command_buffer_secondary = VK_NULL_HANDLE;
  vk::binding::structure::Binding binding;
  vk::structure::Buffer_set buffer;

  //---------------------------
};

}
