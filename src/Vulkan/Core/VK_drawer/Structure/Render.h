#pragma once

#include <Vulkan/Core/VK_commandbuffer/Structure/Command_buffer.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <Vulkan/Core/VK_data/Structure/Object.h>
#include <Utility/Namespace.h>
#include <memory>


namespace vk::structure{

struct Render{
  //---------------------------

  sys::timer::Timepoint ts;
  std::shared_ptr<vk::structure::Renderpass> renderpass;
  std::shared_ptr<vk::structure::Subpass> subpass;
  std::shared_ptr<vk::structure::Pipeline> pipeline;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  std::shared_ptr<vk::structure::Descriptor_set> descriptor_set;
  std::shared_ptr<vk::structure::Object> object;

  //---------------------------
};

}
