#pragma once

#include <Vulkan/VK_pool/Structure/Fence.h>
#include <Vulkan/VK_pool/Structure/Semaphore.h>
#include <Vulkan/VK_pool/Structure/Descriptor.h>


namespace vk::structure{

struct Pool{
  //---------------------------

  vk::pool::Fence fence;
  vk::pool::Semaphore semaphore;
  vk::pool::Descriptor descriptor;

  //---------------------------
};

}
