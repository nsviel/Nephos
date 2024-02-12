#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
namespace vk::pool{class Command_buffer;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::command{class Command;}
namespace vk::main{class Thread;}


namespace vk::command{

class Command_buffer
{
public:
  //Constructor / Destructor
  Command_buffer(vk::structure::Vulkan* struct_vulkan);
  ~Command_buffer();

public:
  //Pool function
  void init_pool(vk::pool::Command_buffer* pool);
  void reset_pool(vk::pool::Command_buffer* pool);
  void clean_pool();
  void submit_pool();

  //Command buffer function
  void create_command_buffer_primary(vk::structure::Command_buffer* command_buffer);
  void create_command_buffer_secondary(vk::structure::Object* data);
  void reset(vk::structure::Command_buffer* command_buffer);
  void submit(vk::structure::Command_buffer* command_buffer);

  //Command buffer lifetime
  vk::structure::Command_buffer* query_free_command_buffer();
  void start_command_buffer_primary(vk::structure::Command_buffer* command_buffer);
  void start_command_buffer_secondary(vk::structure::Renderpass* renderpass);
  void end_command_buffer(vk::structure::Command_buffer* command_buffer);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::synchro::Fence* vk_fence;
  vk::command::Command* vk_command;
  vk::main::Thread* vk_thread;
};

}
