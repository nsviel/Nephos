#pragma once

#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <Vulkan/Core/VK_data/Structure/Data.h>
#include <Vulkan/Core/VK_queue/Structure/Class.h>
#include <Vulkan/Core/VK_device/Structure/Logical.h>
#include <Vulkan/Core/VK_instance/Structure/Instance.h>
#include <Vulkan/Core/VK_presentation/Structure/Swapchain.h>
#include <Vulkan/Core/VK_pool/Structure/Pool.h>
#include <Vulkan/Core/VK_presentation/Structure/Viewport.h>

#include <Vulkan/Render/VK_engine/Structure/Profiler.h>
#include <Vulkan/Render/VK_pipeline/Structure/Structure.h>
#include <Vulkan/Render/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Render/VK_engine/Structure/Parameter.h>
#include <Vulkan/Render/VK_engine/Structure/Profiler.h>

#include <Vulkan/Window/VK_window/Structure/Window.h>
#include <Vulkan/Window/VK_gui/Structure.h>


namespace vk{

struct Structure{
  //---------------------------

  //Constructor
  Structure(bool* running){
    this->window.running = running;
  }

  //Structure
  vk::structure::Window window;
  vk::structure::Panel panel;
  vk::structure::Instance instance;
  vk::structure::Viewport viewport;
  vk::device::structure::Logical device;
  vk::structure::Swapchain swapchain;
  vk::data::structure::Data data;
  vk::structure::Parameter param;
  vk::pool::structure::Pool pools;
  vk::structure::Command command;
  vk::profiler::Structure profiler;
  vk::queue::structure::Class queue;
  vk::render::pipeline::Structure render;
  vk::render::structure::Renderpass renderpass;
  vk::gui::Structure gui;

  //---------------------------
};

}
