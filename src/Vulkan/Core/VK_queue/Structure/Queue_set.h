#pragma once

#include <Vulkan/Core/VK_queue/Structure/Queue.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Queue_set{
  //---------------------------

  vk::structure::Queue graphics;
  vk::structure::Queue presentation;
  vk::structure::Queue transfer;

  //---------------------------
};


}
