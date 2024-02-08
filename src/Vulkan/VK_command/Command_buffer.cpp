#include "Command_buffer.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command_buffer::Command_buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Command_buffer::~Command_buffer(){}

//Main function
void Command_buffer::init(){
  std::vector<vk::structure::Command_buffer>& pool = struct_vulkan->pools.command_buffer.pool;
  //---------------------------

  for(int i=0; i<struct_vulkan->pools.command_buffer.size; i++){
    vk::structure::Command_buffer command_buffer;

    //Fence
    VkFenceCreateInfo fence_info = {};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = 0;
    vkCreateFence(struct_vulkan->device.device, &fence_info, nullptr, &command_buffer.fence);

    //Command buffer
    this->allocate_command_buffer_primary(&command_buffer);
    command_buffer.is_available = true;
    command_buffer.is_recorded = false;

    pool.push_back(command_buffer);
  }

  //---------------------------
}
void Command_buffer::reset(){
  std::vector<vk::structure::Command_buffer>& pool = struct_vulkan->pools.command_buffer.pool;
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<pool.size(); i++){
    vk::structure::Command_buffer* command_buffer = &pool[i];

    if(command_buffer->is_resetable){
      //vkResetCommandBuffer(command_buffer->command, 0);
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
    }
  }

  //---------------------------
}
void Command_buffer::clean(){
  std::vector<vk::structure::Command_buffer>& pool = struct_vulkan->pools.command_buffer.pool;
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<pool.size(); i++){
    vk::structure::Command_buffer* command_buffer = &pool[i];

    //Fence
    vkDestroyFence(struct_vulkan->device.device, command_buffer->fence, nullptr);

    //Command buffer
    vkFreeCommandBuffers(struct_vulkan->device.device, struct_vulkan->pools.command_buffer.command, 1, &command_buffer->command);
  }

  //---------------------------
}
void Command_buffer::submit(){
  std::vector<vk::structure::Command_buffer>& pool = struct_vulkan->pools.command_buffer.pool;
  //---------------------------

  //Submit all recorder command buffer
  vector<VkCommandBuffer> vec_command;
  for(int i=0; i<pool.size(); i++){
    vk::structure::Command_buffer* command_buffer = &pool[i];

    if(command_buffer->is_recorded){
      vec_command.push_back(command_buffer->command);
      command_buffer->is_recorded = false;
    }
  }

  this->submit_command_buffer(vec_command);
  vkQueueWaitIdle(struct_vulkan->device.queue_graphics);

  //Reset all command buffer
  this->reset();

  //---------------------------
}

//Per command buffer
void Command_buffer::reset(vk::structure::Command_buffer* command_buffer){
  std::vector<vk::structure::Command_buffer>& pool = struct_vulkan->pools.command_buffer.pool;
  //---------------------------

  if(command_buffer->is_resetable){
    vkResetCommandBuffer(command_buffer->command, 0);
    command_buffer->is_available = true;
    command_buffer->is_recorded = false;
  }

  //---------------------------
}
void Command_buffer::submit(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  if(command_buffer->is_recorded){
    vector<VkCommandBuffer> vec_command(1, command_buffer->command);
    this->submit_command_buffer(vec_command);
    vkQueueWaitIdle(struct_vulkan->device.queue_graphics);
    command_buffer->is_recorded = false;
  }

  //Reset all command buffer
  this->reset(command_buffer);

  //---------------------------
}

//Command buffer lifetime
vk::structure::Command_buffer* Command_buffer::acquire_free_command_buffer(){
  std::vector<vk::structure::Command_buffer>& pool = struct_vulkan->pools.command_buffer.pool;
  //---------------------------

  //Find the first free command buffer
  for(int i=0; i<pool.size(); i++){
    vk::structure::Command_buffer* command_buffer = &pool[i];

    if(command_buffer->is_available && command_buffer->is_recorded == false){
      vkResetCommandBuffer(command_buffer->command, 0);
      command_buffer->is_available = false;
      return command_buffer;
    }
  }

  //Error message
  cout<<"[error] not enough free command buffer"<<endl;

  //---------------------------
  return nullptr;
}
void Command_buffer::allocate_command_buffer_primary(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool = struct_vulkan->pools.command_buffer.command;
  alloc_info.commandBufferCount = 1;
  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &command_buffer->command);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void Command_buffer::allocate_command_buffer_secondary(vk::structure::Object* data){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
  alloc_info.commandPool = struct_vulkan->pools.command_buffer.command;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &data->command_buffer_secondary);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
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

  //---------------------------
}
void Command_buffer::start_command_buffer_secondary(vk::structure::Renderpass* renderpass){
  vk::structure::Framebuffer* frame = renderpass->framebuffer;
  //---------------------------

  // Create a VkCommandBufferInheritanceInfo structure
  VkCommandBufferInheritanceInfo inheritanceInfo = {};
  inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  inheritanceInfo.pNext = nullptr;
  inheritanceInfo.renderPass = renderpass->renderpass; // The render pass to inherit from
  inheritanceInfo.subpass = 0;       // The subpass to inherit from
  inheritanceInfo.framebuffer = frame->fbo; // The framebuffer to inherit from
  inheritanceInfo.occlusionQueryEnable = VK_FALSE; // Whether to enable occlusion query
  inheritanceInfo.queryFlags = 0; // Query flags (if any)
  inheritanceInfo.pipelineStatistics = 0; // Pipeline statistics (if any)

  // Create a VkCommandBufferBeginInfo structure and set the inheritance info
  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.pNext = nullptr;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT; // Optional flags
  begin_info.pInheritanceInfo = &inheritanceInfo;

  VkResult result = vkBeginCommandBuffer(renderpass->command_buffer->command, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //---------------------------
}
void Command_buffer::end_command_buffer(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  VkResult result = vkEndCommandBuffer(command_buffer->command);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  command_buffer->is_recorded = true;

  //---------------------------
}
void Command_buffer::submit_command_buffer(vector<VkCommandBuffer>& vec_command){
  //---------------------------

  VkSubmitInfo submit_info = {};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = vec_command.size();
  submit_info.pCommandBuffers = vec_command.data();
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, VK_NULL_HANDLE);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  //---------------------------
}

}
