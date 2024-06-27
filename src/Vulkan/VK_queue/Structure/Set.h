#pragma once

#include <Vulkan/VK_queue/Structure/Queue.h>
#include <vulkan/vulkan.h>


namespace vk::queue::structure{

struct Set{
  //---------------------------

  vk::queue::structure::Queue graphics;
  vk::queue::structure::Queue presentation;
  vk::queue::structure::Queue transfer;

  //---------------------------
};


}
