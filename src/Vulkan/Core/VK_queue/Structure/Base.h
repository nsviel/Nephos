#pragma once

#include <Vulkan/Core/VK_command/Structure/Command.h>
#include <memory>


namespace vk::queue{

struct Base{
  //---------------------------

  virtual void add_command(std::unique_ptr<vk::structure::Command> command){}

  //---------------------------
};

}
