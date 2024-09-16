#include "Query.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Query::Query(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Query::~Query(){}

//Main function
vk::pool::structure::Query Query::create_query_pool(){
  //---------------------------

  vk::pool::structure::Query query_pool;
  query_pool.nb_query = 10;

  // Allocate space in the query pool for timestamp queries
  VkQueryPoolCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
  info.queryType = VK_QUERY_TYPE_TIMESTAMP;
  info.queryCount = query_pool.nb_query; // Number of timestamp queries to perform
  vkCreateQueryPool(vk_struct->core.device.handle, &info, nullptr, &query_pool.pool);

  //---------------------------
  return query_pool;
}
void Query::clean_query_pool(vk::pool::structure::Query* query_pool){
  //---------------------------

  vkDestroyQueryPool(vk_struct->core.device.handle, query_pool->pool, nullptr);

  //---------------------------
}

//Subfunction
void Query::begin_query_pass(vk::structure::Command_buffer& command_buffer){
  //---------------------------

  // Begin the query pass
  command_buffer.query.is_available = false;
  vkCmdResetQueryPool(command_buffer.handle, command_buffer.query.pool, 0, command_buffer.query.nb_query);

  // Insert vkCmdWriteTimestamp commands where needed
  vkCmdWriteTimestamp(command_buffer.handle, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, command_buffer.query.pool, 0);

  //---------------------------
}
void Query::end_query_pass(vk::structure::Command_buffer& command_buffer){
  //---------------------------

  vkCmdWriteTimestamp(command_buffer.handle, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, command_buffer.query.pool, 1);

  //---------------------------
}
void Query::find_query_timestamp(vk::structure::Command_buffer& command_buffer){
  vk::pool::structure::Query* query = &command_buffer.query;
  //---------------------------

  uint64_t timestamps[query->nb_query];
  vkGetQueryPoolResults(vk_struct->core.device.handle, query->pool, 0, query->nb_query, sizeof(uint64_t) * query->nb_query, timestamps, sizeof(uint64_t), VK_QUERY_RESULT_64_BIT);

  float delta = float(timestamps[1] - timestamps[0]) * vk_struct->core.device.physical_device.timestamp_period / 1000000000.0f;
  command_buffer.duration = delta;

  vk::profiler::Command_buffer prf_command;
  prf_command.name = command_buffer.name;
  prf_command.duration = command_buffer.duration;
  vk_struct->profiler.vec_command_buffer.push_back(prf_command);

  //---------------------------
}

}
