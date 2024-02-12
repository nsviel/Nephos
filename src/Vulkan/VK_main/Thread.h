#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::pool{class Command_buffer;}


namespace vk::main{

class Thread
{
public:
  //Constructor / Destructor
  Thread(vk::structure::Vulkan* struct_vulkan);
  ~Thread();

public:
  //Main functions
  void init();
  vk::pool::Command_buffer* query_current_command_pool();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
