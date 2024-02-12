#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::pool{class Command_buffer;}
namespace vk::command{class Command_buffer;}
namespace vk::instance{class Pool;}


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
  void reset();
  void clean();
  void submit_commands();

  //Subfunction
  void create_thread_command_pool();
  vk::pool::Command_buffer* query_current_command_pool();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::instance::Pool* vk_pool;
  vk::command::Command_buffer* vk_command_buffer;
};

}
