#pragma once

#include <memory>
#include <string>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::pool::structure{class Command_buffer;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Object;}
namespace vk::structure{class Queue;}
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
  void start_command_buffer_primary(vk::structure::Command_buffer& command_buffer);
  void start_command_buffer_secondary(vk::structure::Renderpass* renderpass);
  void end_command_buffer(vk::structure::Command_buffer& command_buffer);

  //Subfunction
  std::shared_ptr<vk::structure::Command_buffer> query_graphics_command_buffer(std::string name);
  std::shared_ptr<vk::structure::Command_buffer> query_transfer_command_buffer(std::string name);
  std::shared_ptr<vk::structure::Command_buffer> query_free_command_buffer(vk::structure::Queue& queue);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::instance::Query* vk_query;
  vk::instance::UID* vk_uid;
};

}
