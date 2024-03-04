#include "Graphics.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Graphics::Graphics(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_query = new vk::instance::Query(struct_vulkan);

  //---------------------------
  this->start_thread();
}
Graphics::~Graphics(){}

//Main function
void Graphics::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Graphics::run_thread, this);
  }

  //---------------------------
}
void Graphics::run_thread(){
  //---------------------------

  this->thread_running = true;
  while(thread_running){
    this->wait_for_command();
    this->reset_for_submission();
    this->prepare_submission();
    this->queue_submission();
    this->post_submission();
  }

  //---------------------------
}
void Graphics::add_command(vk::structure::Command* command){
  //---------------------------

  vec_command_prepa.push_back(command);
  this->queue_idle = false;

  this->reset_for_submission();
  this->prepare_submission();
  this->queue_submission();
  this->post_submission();

  //---------------------------
}
void Graphics::add_command_thread(vk::structure::Command* command){
  //---------------------------

  vec_command_prepa.push_back(command);

  //---------------------------
}
void Graphics::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(queue_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Graphics::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  this->queue_idle = true;

  while(vec_command_prepa.empty() || struct_vulkan->queue.standby){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  this->queue_idle = false;

  //---------------------------
}
void Graphics::reset_for_submission(){
  //---------------------------

  this->vec_command_buffer.clear();
  this->vec_semaphore_processing.clear();
  this->vec_semaphore_done.clear();
  this->vec_wait_stage.clear();

  //---------------------------
}
void Graphics::prepare_submission(){
  //---------------------------

  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();

  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    //Command buffer
    for(int i=0; i<command->vec_command_buffer.size(); i++){
      vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];
      this->vec_command_buffer.push_back(command_buffer->command);
    }

    //Semaphore processing
    for(int i=0; i<command->vec_semaphore_processing.size(); i++){
      this->vec_semaphore_processing.push_back(command->vec_semaphore_processing[i]);
    }

    //Semaphore done
    for(int i=0; i<command->vec_semaphore_done.size(); i++){
      this->vec_semaphore_done.push_back(command->vec_semaphore_done[i]);
    }

    //Pipeline wait stage
    for(int i=0; i<command->vec_wait_stage.size(); i++){
      this->vec_wait_stage.push_back(command->vec_wait_stage[i]);
    }
  }

  //---------------------------
}
void Graphics::queue_submission(){
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
void Graphics::post_submission(){
  //---------------------------

  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    for(int i=0; i<command->vec_command_buffer.size(); i++){
      vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];

      //Command buffer timestamp
      vk_query->find_query_timestamp(command_buffer);

      //Command buffer reset
      if(command_buffer->is_resetable){
        command_buffer->is_available = true;
        command_buffer->is_recorded = false;
        command_buffer->query.is_in_use = false;
      }
    }
  }

  this->queue_idle = true;

  //---------------------------
}

}
