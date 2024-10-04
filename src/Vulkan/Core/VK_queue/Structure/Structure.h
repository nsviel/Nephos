#pragma once

#include <Vulkan/Core/VK_queue/Transfer/Command.h>
#include <Vulkan/Core/VK_queue/Graphics/Command.h>
#include <Vulkan/Core/VK_queue/Presentation/Command.h>


namespace vk::queue{

struct Structure{
  //---------------------------

  bool standby = false;
  vk::queue::transfer::Command* transfer;
  vk::queue::graphics::Command* graphics;
  vk::queue::presentation::Command* presentation;

  //---------------------------
};

}
