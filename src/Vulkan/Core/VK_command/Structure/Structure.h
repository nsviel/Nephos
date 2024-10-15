#pragma once

#include <Vulkan/Core/VK_queue/Transfer/Command.h>
#include <Vulkan/Core/VK_queue/Graphics/Command.h>
#include <Vulkan/Core/VK_queue/Presentation/Command.h>


namespace vk::command{

struct Structure{
  //---------------------------

  vk::queue::transfer::Command* transfer;
  vk::queue::graphics::Command* graphics;
  vk::queue::presentation::Command* presentation;

  //---------------------------
};

}
