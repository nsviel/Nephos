#pragma once

#include <Vulkan/Core/Structure.h>

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
  vk::structure::Parameter param;
  vk::profiler::Structure profiler;
  vk::render::pipeline::Structure render;
  vk::render::structure::Renderpass renderpass;
  vk::gui::Structure gui;


  vk::core::Structure core;

  //---------------------------
};

}
