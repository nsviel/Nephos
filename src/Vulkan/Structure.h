#pragma once

#include <Vulkan/Core/Structure.h>
#include <Vulkan/Render/Structure.h>
#include <Vulkan/Window/VK_window/Structure/Window.h>
#include <Vulkan/Interface/Parameter.h>
#include <Vulkan/Interface/State.h>


namespace vk{

struct Structure{
  //---------------------------

  //Constructor
  Structure(bool* running){
    this->window.running = running;
  }

  //Structure
  vk::core::Structure core;
  vk::render::Structure render;
  vk::structure::Window window;
  vk::structure::Parameter param;
  vk::structure::State state;

  //---------------------------
};

}
