#pragma once

#include <Vulkan/Core/VK_data/Structure/Structure.h>
#include <Vulkan/Core/VK_queue/Structure/Structure.h>
#include <Vulkan/Core/VK_device/Structure/Logical.h>
#include <Vulkan/Core/VK_instance/Structure/Instance.h>
#include <Vulkan/Core/VK_presentation/Structure/Swapchain.h>
#include <Vulkan/Core/VK_pool/Structure/Structure.h>
#include <Vulkan/Core/VK_presentation/Structure/Viewport.h>
#include <Vulkan/Core/VK_commandbuffer/Structure/Profiler.h>
#include <Vulkan/Core/VK_pipeline/Structure/Structure.h>
#include <Vulkan/Core/VK_presentation/Structure/Structure.h>
#include <Vulkan/Core/VK_validation/Structure.h>
#include <Vulkan/Core/VK_drawer/Structure/Structure.h>


namespace vk::core{

struct Structure{
  //---------------------------

  vk::structure::Instance instance;
  vk::structure::Viewport viewport;
  vk::structure::Logical device;
  vk::structure::Swapchain swapchain;
  vk::data::Structure data;
  vk::pool::Structure pools;
  vk::queue::Structure queue;
  vk::profiler::Structure profiler;
  vk::pipeline::Structure pipeline;
  vk::presentation::Structure presentation;
  vk::validation::Structure validation;
  vk::drawer::Structure drawer;

  //---------------------------
};

}
