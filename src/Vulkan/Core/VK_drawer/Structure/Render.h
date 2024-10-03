#pragma once

#include <Vulkan/Core/VK_commandbuffer/Structure/Command_buffer.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <memory>


namespace vk::structure{

struct Render{
  //---------------------------

  std::shared_ptr<vk::structure::Subpass> subpass;
  std::shared_ptr<vk::structure::Pipeline> pipeline;
  std::shared_ptr<vk::structure::Descriptor_set> descriptor_set;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;

  //---------------------------
};

}
