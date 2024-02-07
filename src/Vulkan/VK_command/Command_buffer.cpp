#include "Command_buffer.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command_buffer::Command_buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_submit = new vk::command::Submit(struct_vulkan);

  //---------------------------
}
Command_buffer::~Command_buffer(){}

//Main function
void Command_buffer::init(){
  std::vector<vk::structure::Command_buffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  for(int i=0; i<struct_vulkan->command.nb_command_buffer; i++){
    vk::structure::Command_buffer command_buffer;

    this->allocate_command_buffer_primary(&command_buffer);
    command_buffer.is_available = true;
    command_buffer.is_for_submit = false;
    vec_command_buffer.push_back(command_buffer);
  }

  //---------------------------
}
void Command_buffer::reset(){
  std::vector<vk::structure::Command_buffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = &vec_command_buffer[i];

    vkResetCommandBuffer(command_buffer->command, 0);
    command_buffer->is_available = true;
    command_buffer->is_for_submit = false;
  }

  //---------------------------
}
void Command_buffer::clean(){
  std::vector<vk::structure::Command_buffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = &vec_command_buffer[i];

    vkFreeCommandBuffers(struct_vulkan->device.device, struct_vulkan->pool.command, 1, &command_buffer->command);
    struct_vulkan->pool.nb_command_buffer--;
  }

  //---------------------------
}
void Command_buffer::submit(){
  std::vector<vk::structure::Command_buffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  //Clear all old command buffer
  for(int i=0; i<vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = &vec_command_buffer[i];

    if(command_buffer->is_for_submit){
      vk_submit->submit_command_graphics(command_buffer->command);
      vkQueueWaitIdle(struct_vulkan->device.queue_graphics);
      command_buffer->is_for_submit = false;
    }
  }

  //---------------------------
}

//Subfunction
vk::structure::Command_buffer* Command_buffer::acquire_free_command_buffer(){
  std::vector<vk::structure::Command_buffer>& vec_command_buffer = struct_vulkan->command.vec_command_buffer;
  //---------------------------

  //Find the first free command buffer
  for(int i=0; i<vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = &vec_command_buffer[i];

    if(command_buffer->is_available && command_buffer->is_for_submit == false){
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
  alloc_info.commandPool = struct_vulkan->pool.command;
  alloc_info.commandBufferCount = 1;
  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &command_buffer->command);
  if(result == VK_SUCCESS){
    struct_vulkan->pool.nb_command_buffer++;
  }else{
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void Command_buffer::start_command_buffer(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  VkResult result = vkBeginCommandBuffer(command_buffer->command, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //---------------------------
}
void Command_buffer::end_command_buffer(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  vkEndCommandBuffer(command_buffer->command);
  command_buffer->is_for_submit = true;

  //---------------------------
}

}
