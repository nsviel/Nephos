#pragma once

#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Vulkan/Core/VK_texture/Structure/Texture.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_data/Structure/Vertex.h>
#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <unordered_map>
#include <memory>


namespace vk::structure{

struct Object{
  //---------------------------

  int UID = 0;
  std::shared_ptr<utl::base::Data> data = std::make_shared<utl::base::Data>();
  std::shared_ptr<utl::base::Pose> pose = std::make_shared<utl::base::Pose>();
  std::unordered_map<std::string, std::shared_ptr<vk::structure::Texture>> map_texture;
  std::unordered_map<vk::vertex::Type, vk::structure::Vertex> map_vertex;

  //---------------------------
};

}
