#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Submit;}
namespace vk::structure{class Vulkan;}


namespace vk::command{

class Command_buffer
{
public:
  //Constructor / Destructor
  Command_buffer(vk::structure::Vulkan* struct_vulkan);
  ~Command_buffer();

public:
  //Main function
  void init();
  void reset();

  //Subfunction
  VkCommandBuffer allocate_command_buffer_primary();
  void start_command_buffer(VkCommandBuffer& command_buffer);
  void end_command_buffer(VkCommandBuffer& command_buffer);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Submit* vk_submit;
};

}
