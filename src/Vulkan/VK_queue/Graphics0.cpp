#include "Graphics0.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::queue{

//Constructor / Destructor
Graphics0::Graphics0(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);

  //---------------------------
  this->start_thread();
}
Graphics0::~Graphics0(){}

//Main functions
void Graphics0::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Graphics0::run_thread, this);
  }

  //---------------------------
}
void Graphics0::run_thread(){
  //---------------------------

  thread_running = true;
  while(thread_running){
    this->wait_for_command();
    this->reset_for_submission();
    this->prepare_submission();
    this->queue_submission();
    this->post_submission();
  }

  //---------------------------
}
void Graphics0::add_command(vk::structure::Command* command){
  //---------------------------

  vec_command_prepa.push_back(command);

  //---------------------------
}

//Subfunction
void Graphics0::wait_for_command(){
  //---------------------------

  while(vec_command_prepa.empty()){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Graphics0::reset_for_submission(){
  //---------------------------

  this->vec_command_buffer.clear();
  this->vec_semaphore_processing.clear();
  this->vec_semaphore_done.clear();
  this->vec_wait_stage.clear();

  //---------------------------
}
void Graphics0::prepare_submission(){
  //---------------------------

  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();

  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    //Command buffer
    for(int j=0; j<command->vec_command_buffer.size(); j++){
      vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[j];
      this->vec_command_buffer.push_back(command_buffer->command);
    }

    //Semaphore - processing
    for(int j=0; j<command->vec_semaphore_processing.size(); j++){
      VkSemaphore semaphore = command->vec_semaphore_processing[j];
      this->vec_semaphore_processing.push_back(semaphore);
    }

    //Semaphore - done
    for(int j=0; j<command->vec_semaphore_done.size(); j++){
      VkSemaphore semaphore = command->vec_semaphore_done[j];
      this->vec_semaphore_done.push_back(semaphore);
    }

    //Wait stage
    for(int j=0; j<command->vec_wait_stage.size(); j++){
      VkPipelineStageFlags wait_stage = command->vec_wait_stage[j];
      this->vec_wait_stage.push_back(wait_stage);
    }
  }

  //---------------------------
}
void Graphics0::queue_submission(){
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

  vkWaitForFences(struct_vulkan->device.handle, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Graphics0::post_submission(){
  //---------------------------

  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    //Reset command buffer
    for(int i=0; i<command->vec_command_buffer.size(); i++){
      vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];

      if(command_buffer->is_resetable){
        command_buffer->is_available = true;
        command_buffer->is_recorded = false;
      }
    }

    delete command;
  }

  this->vec_command_onrun.clear();
  this->vec_command_buffer.clear();

  //---------------------------
}

}
