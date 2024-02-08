#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}


namespace vk::command{

class Submit
{
public:
  //Constructor / Destructor
  Submit(vk::structure::Vulkan* struct_vulkan);
  ~Submit();

public:
  //Main functions
  void submit_rendering_command_buffer(vk::structure::Command* commands);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
