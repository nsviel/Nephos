#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::pool::structure{class Query;}


namespace vk::instance{

class Query
{
public:
  //Constructor / Destructor
  Query(vk::Structure* vk_struct);
  ~Query();

public:
  //Main function
  vk::pool::structure::Query create_query_pool();
  void clean_query_pool(vk::pool::structure::Query* query_pool);

  //Subfunction
  void begin_query_pass(vk::structure::Command_buffer* command_buffer);
  void end_query_pass(vk::structure::Command_buffer* command_buffer);
  void find_query_timestamp(vk::structure::Command_buffer* command_buffer);

private:
  vk::Structure* vk_struct;
};

}
