#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::pool::structure{class Command_buffer;}
namespace vk::synchro{class Fence;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::instance{class UID;}
namespace vk::instance{class Query;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::structure{class Fence;}


namespace vk::commandbuffer{

class Pool
{
public:
  //Constructor / Destructor
  Pool(vk::Structure* vk_struct);
  ~Pool();

public:
  //Main function
  void init_pool(vk::pool::structure::Command_buffer* pool);
  void reset_pool(vk::pool::structure::Command_buffer* pool);
  void clean_pool(vk::pool::structure::Command_buffer* pool);

  //Subfunction
  void create_command_buffer_primary(vk::pool::structure::Command_buffer* pool, vk::structure::Command_buffer& command_buffer);
  void create_command_buffer_secondary(vk::structure::Object* data);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::instance::Query* vk_query;
  vk::instance::UID* vk_uid;
};

}
