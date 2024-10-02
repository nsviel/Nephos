#include "Command_buffer.h"

#include <Vulkan/Namespace.h>
#include <random>


namespace vk::commandbuffer{

//Constructor / Destructor
Command_buffer::Command_buffer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

  //---------------------------
}
Command_buffer::~Command_buffer(){}

//Main function
std::shared_ptr<vk::structure::Command_buffer> Command_buffer::query_free_command_buffer(vk::queue::structure::Queue& queue){
  //---------------------------

  vk::pool::structure::Command_buffer* pool = vk_allocator->query_free_pool(queue);
  if(pool == nullptr) return nullptr;

  // Random number generator setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, pool->size - 1);

  // Find a random available and unrecorded command buffer
  int index;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  do{
    index = distr(gen);
    command_buffer = pool->tank[index];

    std::lock_guard<std::mutex> lock(command_buffer->mutex);
    if(command_buffer->is_available){
      //say(index);
      //say(command_buffer->handle);
      command_buffer->is_available = false;
      vkResetCommandBuffer(command_buffer->handle, 0);
      return command_buffer;
    }
  }while(true);

  //Error message
  std::cout<<"[error] not enough free command buffer"<<std::endl;

  //---------------------------
  return nullptr;
}
void Command_buffer::submit_command_buffer(std::shared_ptr<vk::structure::Command_buffer> command_buffer, vk::queue::Base* queue){
  //---------------------------

  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->command_buffer = command_buffer;
  queue->add_command(std::move(command));

  //---------------------------
}
void Command_buffer::start_command_buffer_primary(vk::structure::Command_buffer& command_buffer){
  //---------------------------

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = 0;
  VkResult result = vkBeginCommandBuffer(command_buffer.handle, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  vk_query->begin_query_pass(command_buffer);

  //---------------------------
}
void Command_buffer::start_command_buffer_secondary(vk::structure::Renderpass* renderpass){
  vk::structure::Framebuffer& frame = renderpass->framebuffer;
  //---------------------------
/*
  // Create a VkCommandBufferInheritanceInfo structure
  VkCommandBufferInheritanceInfo inheritanceInfo = {};
  inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  inheritanceInfo.pNext = nullptr;
  inheritanceInfo.renderPass = renderpass->handle; // The render pass to inherit from
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

  VkResult result = vkBeginCommandBuffer(renderpasx<sqss->command_buffer->handle, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }
*/
  //---------------------------
}
void Command_buffer::end_command_buffer(vk::structure::Command_buffer& command_buffer){
  //---------------------------

  vk_query->end_query_pass(command_buffer);

  VkResult result = vkEndCommandBuffer(command_buffer.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  command_buffer.is_recorded = true;

  //---------------------------
}
int Command_buffer::find_num_available_command(vk::pool::structure::Command_buffer* pool){
  int num = 0;
  //---------------------------

  for(auto& command_buffer : pool->tank){
    if(command_buffer->is_available){
      num++;
    }
  }

  //---------------------------
  return num;
}

}
