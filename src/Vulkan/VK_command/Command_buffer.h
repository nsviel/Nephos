#pragma once

#include <Utility/Specific/common.h>

namespace vk::command{class Submit;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}


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
  void clean();
  void submit();

  //Per command buffer
  void reset(vk::structure::Command_buffer* command_buffer);
  void submit(vk::structure::Command_buffer* command_buffer);

  //Subfunction
  vk::structure::Command_buffer* acquire_free_command_buffer();
  void allocate_command_buffer_primary(vk::structure::Command_buffer* command_buffer);
  void start_command_buffer(vk::structure::Command_buffer* command_buffer);
  void end_command_buffer(vk::structure::Command_buffer* command_buffer);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::command::Submit* vk_submit;
};

}
