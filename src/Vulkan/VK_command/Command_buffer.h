#pragma once

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
namespace vk::pool::structure{class Command_buffer;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::synchro::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::command{class Allocator;}
namespace vk::instance{class UID;}
namespace vk::instance{class Query;}


namespace vk::command{

class Command_buffer
{
public:
  //Constructor / Destructor
  Command_buffer(vk::structure::Vulkan* vk_struct);
  ~Command_buffer();

public:
  //Pool function
  void init_pool(vk::pool::structure::Command_buffer* pool);
  void reset_pool(vk::pool::structure::Command_buffer* pool);
  void clean_pool(vk::pool::structure::Command_buffer* pool);

  //Command buffer function
  void create_command_buffer_primary(vk::pool::structure::Command_buffer* pool, vk::structure::Command_buffer* command_buffer);
  void create_command_buffer_secondary(vk::structure::Object* data);

  //Command buffer lifetime
  vk::structure::Command_buffer* query_free_command_buffer(vk::pool::structure::Command_buffer* pool);
  void start_command_buffer_primary(vk::structure::Command_buffer* command_buffer);
  void start_command_buffer_secondary(vk::structure::Renderpass* renderpass);
  void end_command_buffer(vk::structure::Command_buffer* command_buffer);
  int find_num_available_command(vk::pool::structure::Command_buffer* pool);

private:
  vk::structure::Vulkan* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::command::Allocator* vk_allocator;
  vk::instance::Query* vk_query;
  vk::instance::UID* vk_uid;
};

}
