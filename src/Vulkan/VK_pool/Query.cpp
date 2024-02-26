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

  query_pool.nb_query = 2;

  // Allocate space in the query pool for timestamp queries
  VkQueryPoolCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
  info.queryType = VK_QUERY_TYPE_TIMESTAMP;
  info.queryCount = query_pool.nb_query; // Number of timestamp queries to perform
  vkCreateQueryPool(struct_vulkan->device.handle, &info, nullptr, &query_pool.pool);

  //---------------------------
  return query_pool;
}
void Query::clean_query_pool(vk::structure::Query* query_pool){
  //---------------------------

  vkResetQueryPool(struct_vulkan->device.handle, query_pool->pool, 0, query_pool->nb_query);

  //---------------------------
}

//Subfunction
void Query::begin_query_pass(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  // Begin the query pass
  vkCmdResetQueryPool(command_buffer->command, command_buffer->query.pool, 0, command_buffer->query.nb_query);

  // Insert vkCmdWriteTimestamp commands where needed
  vkCmdWriteTimestamp(command_buffer->command, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, command_buffer->query.pool, 0);

  //---------------------------
}
void Query::end_query_pass(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  vkCmdWriteTimestamp(command_buffer->command, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, command_buffer->query.pool, 1);

  //---------------------------
}
void Query::find_query_timestamp(vk::structure::Command_buffer* command_buffer){
  vk::structure::Query* query = &command_buffer->query;
  //---------------------------

  struct_vulkan->profiler->tasker_gpu->task_begin(command_buffer->name, 0);

  uint64_t timestamps[query->nb_query];
  vkGetQueryPoolResults(struct_vulkan->device.handle, query->pool, 0, query->nb_query, sizeof(uint64_t) * query->nb_query, timestamps, sizeof(uint64_t), VK_QUERY_RESULT_64_BIT);

  float delta = float(timestamps[1] - timestamps[0]) * struct_vulkan->device.physical_device.timestamp_period / 1000000000.0f;
  command_buffer->timestamp = delta;

  struct_vulkan->profiler->tasker_gpu->task_end(command_buffer->name, delta);

  //---------------------------
}

}
