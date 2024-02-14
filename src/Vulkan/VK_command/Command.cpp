#include "Command.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command::Command(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);

  //---------------------------
}
Command::~Command(){}

//Main function
void Command::submit_command(vk::structure::Command* command){
  //---------------------------

  this->reset_for_submission();
  this->prepare_submission(command);
  this->queue_submission();
  this->wait_and_reset(command);

  //---------------------------
}

//Subfunction
void Command::reset_for_submission(){
  //---------------------------

  this->vec_command_buffer.clear();
  this->vec_semaphore_processing.clear();
  this->vec_semaphore_done.clear();
  this->vec_wait_stage.clear();

  //---------------------------
}
void Command::prepare_submission(vk::structure::Command* command){
  //---------------------------

  //Command buffer
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];
    this->vec_command_buffer.push_back(command_buffer->command);
  }

  this->vec_semaphore_processing = command->vec_semaphore_processing;
  this->vec_wait_stage = command->vec_wait_stage;
  this->vec_semaphore_done = command->vec_semaphore_done;

  //---------------------------
}
void Command::queue_submission(){
  //---------------------------

  vk::structure::Fence* fence = vk_fence->query_free_fence();

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = vec_semaphore_processing.size();
  submit_info.pWaitSemaphores = vec_semaphore_processing.data();
  submit_info.pWaitDstStageMask = vec_wait_stage.data();
  submit_info.signalSemaphoreCount = vec_semaphore_done.size();
  submit_info.pSignalSemaphores = vec_semaphore_done.data();
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  VkResult result = vkQueueSubmit(struct_vulkan->device.queue.graphics, 1, &submit_info, fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vkWaitForFences(struct_vulkan->device.device, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Command::wait_and_reset(vk::structure::Command* command){
  //---------------------------

  //Reset command buffer
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];

    if(command_buffer->is_resetable){
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
    }
  }

  //---------------------------
}

}
