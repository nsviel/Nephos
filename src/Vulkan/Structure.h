#pragma once

#include <Vulkan/Core/Structure.h>
#include <Vulkan/Render/Structure.h>
#include <Vulkan/Window/VK_window/Structure/Window.h>
#include <Vulkan/Interface/Structure.h>


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
  vk::structure::Interface interface;

  //---------------------------
};

}
