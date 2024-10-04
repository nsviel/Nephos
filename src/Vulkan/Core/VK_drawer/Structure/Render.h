#pragma once

#include <Vulkan/Core/VK_commandbuffer/Structure/Command_buffer.h>
#include <Vulkan/Core/VK_commandbuffer/Structure/Command.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <Vulkan/Core/VK_data/Structure/Object.h>
#include <Vulkan/Core/VK_synchronization/Structure/Semaphore.h>
#include <Utility/Namespace.h>
#include <memory>
#include <vector>


namespace vk::structure{

struct Render{
  //---------------------------

  //Info
  sys::timer::Timepoint ts;
  int subset_ID = 0;

  //Structure
  std::shared_ptr<vk::structure::Renderpass> renderpass;
  std::shared_ptr<vk::structure::Subpass> subpass;
  std::shared_ptr<vk::structure::Pipeline> pipeline;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  std::shared_ptr<vk::structure::Descriptor_set> descriptor_set;
  std::shared_ptr<vk::structure::Object> object;
  std::shared_ptr<vk::structure::Semaphore> semaphore;
  std::vector<std::unique_ptr<vk::structure::Command>> vec_command;

  //---------------------------
};

}
