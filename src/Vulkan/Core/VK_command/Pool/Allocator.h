#pragma once

namespace vk{class Structure;}
namespace vk::queue::structure{class Queue;}
namespace vk::pool::structure{class Command_buffer;}
namespace vk::command{class Command_buffer;}
namespace vk::instance{class Pool;}


namespace vk::command{

class Allocator
{
public:
  //Constructor / Destructor
  Allocator(vk::Structure* vk_struct);
  ~Allocator();

public:
  //Main function
  void init();
  void reset();
  void clean();

  //Subfunction
  void create_command_buffer_pool(vk::queue::structure::Queue& queue);
  void reset_command_buffer_pool(vk::queue::structure::Queue& queue);
  void clean_command_buffer_pool(vk::queue::structure::Queue& queue);

  //Command buffer pool use
  vk::pool::structure::Command_buffer* query_free_pool(vk::queue::structure::Queue& queue);

private:
  vk::Structure* vk_struct;
  vk::instance::Pool* vk_pool;
  vk::command::Command_buffer* vk_command_buffer;
};

}
