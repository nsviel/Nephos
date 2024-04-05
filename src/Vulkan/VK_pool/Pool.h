#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::pool{class Command_buffer;}
namespace vk::main{class Thread;}


namespace vk::instance{

class Pool
{
public:
  //Constructor / Destructor
  Pool(vk::structure::Vulkan* vk_struct);
  ~Pool();

public:
  //Main functions
  void init();
  void clean();

  //Descriptor pool
  void create_descriptor_pool();
  void reset_descriptor_pool();
  void clean_descriptor_pool();

  //Command pool
  void create_command_pool(vk::pool::Command_buffer* pool, int family_ID);
  void reset_command_pool(vk::pool::Command_buffer* pool);
  void clean_command_pool(vk::pool::Command_buffer* pool);

private:
  vk::structure::Vulkan* vk_struct;
  vk::main::Thread* vk_thread;
};

}
