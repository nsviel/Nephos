#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <vulkan/vulkan.h>


namespace vk::command::structure{

struct Set{
  //---------------------------

  std::vector<vk::structure::Command*> vec_command;
  vk::synchro::structure::Fence* fence = nullptr;

  //---------------------------
};

}
