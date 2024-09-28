#pragma once

#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Vulkan/Core/VK_image/Structure/Texture.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <unordered_map>
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

  //Vulkan stuff
  int UID = 0;
  VkCommandBuffer command_buffer_secondary = VK_NULL_HANDLE;
  vk::structure::Descriptor_set descriptor_set;

  //Data
  std::shared_ptr<utl::base::Data> data = std::make_shared<utl::base::Data>();
  std::shared_ptr<utl::base::Pose> pose = std::make_shared<utl::base::Pose>();
  std::unordered_map<std::string, std::shared_ptr<vk::structure::Texture>> map_texture;
  vk::structure::Buffer_set buffer;

  //---------------------------
};

}
