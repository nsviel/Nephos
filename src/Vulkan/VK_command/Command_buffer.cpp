#include "Command_buffer.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command_buffer::Command_buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_thread = new vk::command::Allocator(struct_vulkan);
  this->vk_uid = new vk::instance::UID(struct_vulkan);
  this->vk_query = new vk::instance::Query(struct_vulkan);

  //---------------------------
}
Command_buffer::~Command_buffer(){}

//Pool function
void Command_buffer::init_pool(vk::pool::Command_buffer* pool){
  //---------------------------

  for(int i=0; i<pool->size; i++){
    vk::structure::Command_buffer command_buffer;
    command_buffer.is_available = true;
    command_buffer.is_recorded = false;
    command_buffer.UID = vk_uid->query_free_UID();
    command_buffer.query = vk_query->create_query_pool();

    this->create_command_buffer_primary(pool, &command_buffer);
    pool->tank.push_back(command_buffer);
  }

  //---------------------------
}
void Command_buffer::reset_pool(vk::pool::Command_buffer* pool){
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<pool->size; i++){
    vk::structure::Command_buffer* command_buffer = &pool->tank[i];

    if(command_buffer->is_resetable){
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
    }
  }

  //---------------------------
}
void Command_buffer::clean_pool(vk::pool::Command_buffer* pool){
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<pool->size; i++){
    vk::structure::Command_buffer* command_buffer = &pool->tank[i];

    vk_query->clean_query_pool(&command_buffer->query);
    vkFreeCommandBuffers(struct_vulkan->device.handle, pool->allocator, 1, &command_buffer->command);
  }

  //---------------------------
}

//Command buffer function
void Command_buffer::create_command_buffer_primary(vk::pool::Command_buffer* pool, vk::structure::Command_buffer* command_buffer){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool = pool->allocator;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.handle, &alloc_info, &command_buffer->command);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void Command_buffer::create_command_buffer_secondary(vk::structure::Object* data){
  vk::pool::Command_buffer* pool = &struct_vulkan->device.queue.transfer.pool;
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
  alloc_info.commandPool = pool->allocator;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.handle, &alloc_info, &data->command_buffer_secondary);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}

//Command buffer lifetime
vk::structure::Command_buffer* Command_buffer::query_free_command_buffer(vk::pool::Command_buffer* pool){
  if(pool == nullptr) return nullptr;
  //---------------------------

  // Random number generator setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, pool->size - 1);

  // Find a random available and unrecorded command buffer
  int index;
  vk::structure::Command_buffer* command_buffer;
  do{
    index = distr(gen);
    command_buffer = &pool->tank[index];

    if(command_buffer->is_available){
      command_buffer->is_available = false;
      return command_buffer;
    }
  }while(true);

  //Error message
  cout<<"[error] not enough free command buffer"<<endl;

  //---------------------------
  return nullptr;
}
void Command_buffer::start_command_buffer_primary(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = 0;
  VkResult result = vkBeginCommandBuffer(command_buffer->command, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  vk_query->begin_query_pass(command_buffer);

  //---------------------------
}
void Command_buffer::start_command_buffer_secondary(vk::structure::Renderpass* renderpass){
  vk::structure::Framebuffer* frame = renderpass->framebuffer;
  //---------------------------
/*
  // Create a VkCommandBufferInheritanceInfo structure
  VkCommandBufferInheritanceInfo inheritanceInfo = {};
  inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  inheritanceInfo.pNext = nullptr;
  inheritanceInfo.renderPass = renderpass->renderpass; // The render pass to inherit from
  inheritanceInfo.subpass = 0;       // The subpass to inherit from
  inheritanceInfo.framebuffer = frame->fbo; // The framebuffer to inherit from
  inheritanceInfo.occlusionQueryEnable = VK_FALSE; // Whether to enable occlusion query
  inheritanceInfo.queryFlags = 0; // Query flags (if any)
  inheritanceInfo.pipelinesubmit_commandStatistics = 0; // Pipeline statistics (if any)

  // Create a VkCommandBufferBeginInfo structure and set the inheritance info
  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.pNext = nullptr;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT; // Optional flags
  begin_info.pInheritanceInfo = &inheritanceInfo;

  VkResult result = vkBeginCommandBuffer(renderpasx<sqss->command_buffer->command, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }
*/
  //---------------------------
}
void Command_buffer::end_command_buffer(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  vk_query->end_query_pass(command_buffer);

  VkResult result = vkEndCommandBuffer(command_buffer->command);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  command_buffer->is_recorded = true;

  //---------------------------
}

}
