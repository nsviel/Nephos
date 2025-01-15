#pragma once

#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <Vulkan/Core/VK_render/Structure/Render.h>
#include <memory>
#include <vector>


namespace vk::structure{

struct Batch{
  //Associated to a set of renderpass operation
  //---------------------------

  std::shared_ptr<vk::structure::Semaphore> semaphore;
  std::vector<std::shared_ptr<vk::structure::Render>> vec_render;
  std::vector<std::unique_ptr<vk::structure::Command>> vec_command;

  //---------------------------
};

}
