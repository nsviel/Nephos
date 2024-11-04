#pragma once

#include <Vulkan/Core/Structure.h>
#include <Vulkan/Graphics/Structure.h>
#include <Vulkan/Window/VK_window/Structure/Window.h>
#include <Vulkan/Interface/Structure.h>


namespace vk{

struct Structure{
  //---------------------------

  vk::core::Structure core;
  vk::graphics::Structure graphics;
  vk::structure::Window window;
  vk::structure::Interface interface;

  //---------------------------
};

}
