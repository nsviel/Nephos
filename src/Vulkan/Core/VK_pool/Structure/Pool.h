#pragma once

#include <Vulkan/Core/VK_pool/Structure/Fence.h>
#include <Vulkan/Core/VK_pool/Structure/Semaphore.h>
#include <Vulkan/Core/VK_pool/Structure/Descriptor_set.h>


namespace vk::pool::structure{

struct Pool{
  //---------------------------

  vk::pool::structure::Fence fence;
  vk::pool::structure::Semaphore semaphore;
  vk::pool::structure::Descriptor_set descriptor_set;

  //---------------------------
};

}