#pragma once

#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Vulkan/Core/VK_texture/Structure/Texture.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <unordered_map>
#include <memory>
#include <list>


namespace vk::structure{

struct Vertex{
  //---------------------------

  vk::structure::Buffer buffer;
  vk::structure::Buffer stagger;
  size_t size = 0;

  //---------------------------
};

}
