#pragma once

#include <Vulkan/Core/VK_queue/Transfer/Queue.h>
#include <Vulkan/Core/VK_queue/Graphics/Queue.h>
#include <Vulkan/Core/VK_queue/Presentation/Queue.h>


namespace vk::queue{

struct Structure{
  //---------------------------

  bool standby = false;
  vk::queue::transfer::Queue* transfer;
  vk::queue::graphics::Queue* graphics;
  vk::queue::presentation::Queue* presentation;

  //---------------------------
};

}
