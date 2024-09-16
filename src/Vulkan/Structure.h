#pragma once

#include <Vulkan/Core/Structure.h>
#include <Vulkan/Render/Structure.h>
#include <Vulkan/Window/Structure.h>


namespace vk{

struct Structure{
  //---------------------------

  //Constructor
  Structure(bool* running){
    this->window.window.running = running;
  }

  //Structure
  vk::core::Structure core;
  vk::render::Structure render;
  vk::window::Structure window;

  //---------------------------
};

}
