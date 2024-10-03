#pragma once

#include <Vulkan/Core/VK_pool/Structure/Fence.h>
#include <Vulkan/Core/VK_pool/Structure/Semaphore.h>
#include <Vulkan/Core/VK_pool/Structure/Descriptor.h>


namespace vk::pool{

struct Structure{
  //---------------------------

  vk::pool::structure::Fence fence;
  vk::pool::structure::Semaphore semaphore;
  vk::pool::structure::Descriptor descriptor;

  //---------------------------
};

}
