#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::pool{class Command_buffer;}
namespace vk::command{class Command_buffer;}
namespace vk::instance{class Pool;}


namespace vk::command{

class Allocator
{
public:
  //Constructor / Destructor
  Allocator(vk::structure::Vulkan* struct_vulkan);
  ~Allocator();

public:
  //Main functions
  void init();
  void reset();
  void clean();

  //Subfunction
  vk::pool::Command_buffer* query_free_allocator_pool();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::instance::Pool* vk_pool;
  vk::command::Command_buffer* vk_command_buffer;
};

}
