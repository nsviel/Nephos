#include "Transfer.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::thread{

//Constructor / Destructor
Transfer::Transfer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);

  //---------------------------
  this->start_thread();
}
Transfer::~Transfer(){}

//Main functions
void Transfer::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Transfer::run_thread, this);
  }

  //---------------------------
}
void Transfer::run_thread(){
  //---------------------------

  thread_running = true;
  while(thread_running){
    this->wait_for_command();

    int nb_command = vec_command.size();
    for(int i=0; i<nb_command; i++){
      vk::structure::Command* command = vec_command[i];

      this->reset_for_submission();
      this->prepare_submission(command);
      this->queue_submission();
      this->wait_and_reset(command);
    }

    //Remove submetetd commands
    vec_command.erase(std::remove(vec_command.begin(), vec_command.end(), nullptr), vec_command.end());
  }

  //---------------------------
}

//Subfunction
void Transfer::wait_for_command(){
  //---------------------------

  while(vec_command.empty()){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Transfer::reset_for_submission(){
  //---------------------------

  this->fence = VK_NULL_HANDLE;
  this->vec_command_buffer.clear();

  //---------------------------
}
void Transfer::prepare_submission(vk::structure::Command* command){
  //---------------------------

  //Fence
  this->fence = vk_fence->query_free_fence();

  //Command buffer
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];
    command_buffer->fence = fence;
    this->vec_command_buffer.push_back(command_buffer->command);
  }

  //---------------------------
}
void Transfer::queue_submission(){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue.transfer, 1, &submit_info, fence->fence);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  //---------------------------
}
void Transfer::wait_and_reset(vk::structure::Command* command){
  //---------------------------

  //vkQueueWaitIdle(struct_vulkan->device.queue.graphics);
  vkWaitForFences(struct_vulkan->device.device, 1, &fence->fence, VK_TRUE, UINT64_MAX);

  //Reset command buffer
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];

    if(command_buffer->is_resetable){
      vkResetCommandBuffer(command_buffer->command, 0);
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
      command_buffer->fence = nullptr;
    }
  }

  vk_fence->reset_fence(fence);
  command = nullptr;

  //---------------------------
}

}
