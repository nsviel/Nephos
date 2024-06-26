#pragma once

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Queue;}
namespace vk::pool{class Command_buffer;}
namespace vk::command{class Command_buffer;}
namespace vk::instance{class Pool;}


namespace vk::command{

class Allocator
{
public:
  //Constructor / Destructor
  Allocator(vk::structure::Vulkan* vk_struct);
  ~Allocator();

public:
  //Main function
  void init();
  void reset();
  void clean();

  //Subfunction
  void create_command_buffer_pool(vk::structure::Queue* queue);
  void reset_command_buffer_pool(vk::structure::Queue* queue);
  void clean_command_buffer_pool(vk::structure::Queue* queue);

  //Command buffer pool use
  vk::pool::Command_buffer* query_free_pool(vk::structure::Queue* queue);

private:
  vk::structure::Vulkan* vk_struct;
  vk::instance::Pool* vk_pool;
  vk::command::Command_buffer* vk_command_buffer;
};

}
