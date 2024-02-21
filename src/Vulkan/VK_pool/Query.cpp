#include "Query.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Query::Query(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Query::~Query(){}

//Main function
vk::structure::Query Query::create_query_pool(){
  vk::structure::Query query_pool;
  //---------------------------

  query_pool.nb_query = 100;

  // Allocate space in the query pool for timestamp queries
  VkQueryPoolCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
  info.queryType = VK_QUERY_TYPE_TIMESTAMP;
  info.queryCount = query_pool.nb_query; // Number of timestamp queries to perform
  vkCreateQueryPool(struct_vulkan->device.device, &info, nullptr, &query_pool.pool);

  //---------------------------
  return query_pool;
}
void Query::begin_query_pass(vk::structure::Command_buffer* command_buffer, vk::structure::Query* query){
  //---------------------------

  // Begin the query pass
  vkCmdResetQueryPool(command_buffer->command, query->pool, 0, query->nb_query);
  vkCmdBeginQuery(command_buffer->command, query->pool, 0, 0);

  // Insert vkCmdWriteTimestamp commands where needed
  vkCmdWriteTimestamp(command_buffer->command, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, query->pool, 0);

  // End the query pass
  vkCmdEndQuery(command_buffer->command, query->pool, 0);

  //---------------------------
}
void Query::find_query_timestamp(vk::structure::Query* query){
  //---------------------------

  uint64_t timestamps[query->nb_query];
  vkGetQueryPoolResults(struct_vulkan->device.device, query->pool, 0, query->nb_query, sizeof(uint64_t) * query->nb_query, timestamps, sizeof(uint64_t), VK_QUERY_RESULT_64_BIT);

  //---------------------------
}

}
