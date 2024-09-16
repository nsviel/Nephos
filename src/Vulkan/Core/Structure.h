#pragma once

#include <Vulkan/Core/VK_data/Structure/Data.h>
#include <Vulkan/Core/VK_queue/Structure/Class.h>
#include <Vulkan/Core/VK_device/Structure/Logical.h>
#include <Vulkan/Core/VK_instance/Structure/Instance.h>
#include <Vulkan/Core/VK_presentation/Structure/Swapchain.h>
#include <Vulkan/Core/VK_pool/Structure/Pool.h>
#include <Vulkan/Core/VK_presentation/Structure/Viewport.h>
#include <Vulkan/Core/VK_command/Structure/Profiler.h>
#include <Vulkan/Core/VK_pipeline/Structure/Structure.h>


namespace vk::core{

struct Structure{
  //---------------------------

  vk::structure::Instance instance;
  vk::structure::Viewport viewport;
  vk::device::structure::Logical device;
  vk::structure::Swapchain swapchain;
  vk::data::structure::Data data;
  vk::pool::structure::Pool pools;
  vk::queue::structure::Class queue;
  vk::profiler::Structure profiler;
  vk::pipeline::Structure pipeline;

  //---------------------------
};

}
