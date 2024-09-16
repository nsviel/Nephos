#pragma once

#include <Vulkan/Core/VK_queue/Transfer/Thread.h>
#include <Vulkan/Core/VK_queue/Graphics/Thread.h>
#include <Vulkan/Core/VK_queue/Presentation/Thread.h>


namespace vk::queue::structure{

struct Class{
  //---------------------------

  bool standby = false;
  vk::queue::transfer::Thread* transfer;
  vk::queue::graphics::Thread* graphics;
  vk::queue::presentation::Thread* presentation;

  //---------------------------
};

}
