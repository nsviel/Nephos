#pragma once

#include <Vulkan/Core/VK_queue/Transfer/Queue.h>
#include <Vulkan/Core/VK_queue/Graphics/Queue.h>
#include <Vulkan/Core/VK_queue/Presentation/Queue.h>


namespace vk::queue::structure{

struct Class{
  //---------------------------

  bool standby = false;
  vk::queue::transfer::Queue* transfer;
  vk::queue::graphics::Queue* graphics;
  vk::queue::presentation::Queue* presentation;

  //---------------------------
};

}
