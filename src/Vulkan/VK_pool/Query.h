#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Query;}


namespace vk::instance{

class Query
{
public:
  //Constructor / Destructor
  Query(vk::structure::Vulkan* struct_vulkan);
  ~Query();

public:
  //Main function
  vk::structure::Query create_query_pool();
  void clean_query_pool(vk::structure::Query* query_pool);

  //Subfunction
  void begin_query_pass(vk::structure::Command_buffer* command_buffer);
  void end_query_pass(vk::structure::Command_buffer* command_buffer);
  void find_query_timestamp(vk::structure::Query* query);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
