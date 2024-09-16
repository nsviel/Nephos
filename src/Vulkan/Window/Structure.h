#pragma once

#include <Vulkan/Window/VK_window/Structure/Window.h>
#include <Vulkan/Window/VK_gui/Structure.h>


namespace vk::window{

struct Structure{
  //---------------------------

  vk::structure::Window window;
  vk::structure::Panel panel;
  vk::gui::Structure gui;

  //---------------------------
};

}
