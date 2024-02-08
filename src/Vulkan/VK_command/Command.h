#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}


namespace vk::command{

class Command
{
public:
  //Constructor / Destructor
  Command(vk::structure::Vulkan* struct_vulkan);
  ~Command();

public:
  //Main function
  void submit_command(vk::structure::Command* commands);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
