#pragma once

#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Vulkan/Core/VK_image/Structure/Texture.h>
#include <Vulkan/Core/VK_binding/Structure/Binding.h>
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
  std::shared_ptr<utl::base::Data> data = std::make_shared<utl::base::Data>();
  std::shared_ptr<utl::base::Pose> pose = std::make_shared<utl::base::Pose>();

  //Binding
  std::list< std::shared_ptr<vk::structure::Texture> > list_vk_texture;
  VkCommandBuffer command_buffer_secondary = VK_NULL_HANDLE;
  vk::structure::Buffer_set buffer;




  vk::descriptor::structure::Binding binding;
  vk::descriptor::structure::Descriptor_set descriptor_set;

  //---------------------------
};

}
