#pragma once

namespace vk{class Structure;}
namespace vk::pool::structure{class Command_buffer;}
namespace vk::main{class Thread;}


namespace vk::instance{

class Pool
{
public:
  //Constructor / Destructor
  Pool(vk::Structure* vk_struct);
  ~Pool();

public:
  //Main function
  void init();
  void clean();

  //Descriptor pool
  void create_descriptor_pool();
  void reset_descriptor_pool();
  void clean_descriptor_pool();

  //Command pool
  void create_command_pool(vk::pool::structure::Command_buffer* pool, int family_ID);
  void reset_command_pool(vk::pool::structure::Command_buffer* pool);
  void clean_command_pool(vk::pool::structure::Command_buffer* pool);

private:
  vk::Structure* vk_struct;
  vk::main::Thread* vk_thread;
};

}
