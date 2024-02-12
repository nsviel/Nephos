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
  bool is_thread_in_engine(int ID);
  vk::pool::Command_buffer* create_thread_command_pool(int ID);
  vk::pool::Command_buffer* query_command_pool(int ID);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::instance::Pool* vk_pool;
  vk::command::Command_buffer* vk_command_buffer;
};

}
