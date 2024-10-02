#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::pool::structure{class Command_buffer;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::queue::structure{class Queue;}
namespace vk::queue{class Base;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::instance{class UID;}
namespace vk::instance{class Query;}


namespace vk::commandbuffer{

class Command_buffer
{
public:
  //Constructor / Destructor
  Command_buffer(vk::Structure* vk_struct);
  ~Command_buffer();

public:
  //Main function
  std::shared_ptr<vk::structure::Command_buffer> query_free_command_buffer(vk::queue::structure::Queue& queue);
  void submit_command_buffer(std::shared_ptr<vk::structure::Command_buffer> command_buffer, vk::queue::Base* queue);
  void start_command_buffer_primary(vk::structure::Command_buffer& command_buffer);
  void start_command_buffer_secondary(vk::structure::Renderpass* renderpass);
  void end_command_buffer(vk::structure::Command_buffer& command_buffer);
  int find_num_available_command(vk::pool::structure::Command_buffer* pool);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::instance::Query* vk_query;
  vk::instance::UID* vk_uid;
};

}
