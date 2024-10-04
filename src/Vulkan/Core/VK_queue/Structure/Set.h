#pragma once

#include <Vulkan/Core/VK_queue/Structure/Queue.h>
#include <vulkan/vulkan.h>


namespace vk::queue::structure{

struct Set{
  //---------------------------

  vk::structure::Queue graphics;
  vk::structure::Queue presentation;
  vk::structure::Queue transfer;

  //---------------------------
};


}
