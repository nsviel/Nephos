#pragma once

#include <Vulkan/VK_queue/Transfer/Thread.h>
#include <Vulkan/VK_queue/Graphics/Thread.h>
#include <Vulkan/VK_queue/Presentation/Presentation.h>


namespace vk::queue::structure{

struct Class{
  //---------------------------

  bool standby = false;
  vk::queue::transfer::Thread* transfer;
  vk::queue::graphics::Thread* graphics;
  vk::queue::Presentation* presentation;

  //---------------------------
};

}
