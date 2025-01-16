#pragma once

#include <Vulkan/Core/VK_commandbuffer/Structure/Command_buffer.h>
#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <Vulkan/Core/VK_framebuffer/Structure/Framebuffer.h>
#include <Vulkan/Core/VK_data/Structure/Object.h>
#include <Vulkan/Core/VK_presentation/Structure/Viewport.h>
#include <Vulkan/Core/VK_synchronization/Structure/Semaphore.h>
#include <Utility/Namespace.h>
#include <memory>
#include <vector>


namespace vk::structure{

struct Render_fbo{
  //---------------------------

  std::shared_ptr<vk::structure::Framebuffer> current;
  std::shared_ptr<vk::structure::Framebuffer> previous;

  //---------------------------
};

struct Render{
  //Associated to renderpass operation
  //---------------------------

  //Info
  sys::timer::Timepoint ts;
  int subset_ID = 0;

  //Structure
  vk::structure::Render_fbo framebuffer;
  std::shared_ptr<vk::structure::Renderpass> renderpass;
  std::shared_ptr<vk::structure::Subpass> subpass;
  std::shared_ptr<vk::structure::Pipeline> pipeline;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  std::shared_ptr<vk::structure::Descriptor_set> descriptor_set;
  std::shared_ptr<vk::structure::Object> object;
  std::shared_ptr<vk::structure::Semaphore> semaphore;
  std::shared_ptr<vk::structure::Fence> fence;
  std::shared_ptr<vk::structure::Viewport> viewport;
  std::unique_ptr<vk::structure::Command> command;

  //---------------------------
};

}
