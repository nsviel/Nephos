#include "Command.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command::Command(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Command::~Command(){}

//Main function
void Command::submit_command_thread(vk::structure::Command* command){
  //---------------------------

  this->thread = std::thread([this, command](){
    this->submit_command(command);
  });

  //---------------------------
}
void Command::submit_command(vk::structure::Command* command){
  //---------------------------

  this->prepare_submission(command);
  this->queue_submission();
  this->wait_and_reset(command);

  //---------------------------
}

//Subfunction
void Command::prepare_submission(vk::structure::Command* command){
  //---------------------------

  //Command buffer
  this->vec_command_buffer.clear();
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];
    this->vec_command_buffer.push_back(command_buffer->command);
  }

  this->vec_semaphore_processing = command->vec_semaphore_processing;
  this->vec_wait_stage = command->vec_wait_stage;
  this->vec_semaphore_done = command->vec_semaphore_done;

  //Fence
  this->fence = VK_NULL_HANDLE;
  if(command->fence != nullptr){
    this->fence = command->fence->fence;
  }

  //Submission
  //this->queue_submission();

  //---------------------------
}
void Command::queue_submission(){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = vec_semaphore_processing.size();
  submit_info.pWaitSemaphores = vec_semaphore_processing.data();
  submit_info.pWaitDstStageMask = vec_wait_stage.data();
  submit_info.signalSemaphoreCount = vec_semaphore_done.size();
  submit_info.pSignalSemaphores = vec_semaphore_done.data();
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, fence);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  //---------------------------
}
void Command::wait_and_reset(vk::structure::Command* command){
  //---------------------------

  vkQueueWaitIdle(struct_vulkan->device.queue_graphics);

  //Reset command buffer
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];

    if(command_buffer->is_resetable){
      vkResetCommandBuffer(command_buffer->command, 0);
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
    }
  }



  //---------------------------
}

}
