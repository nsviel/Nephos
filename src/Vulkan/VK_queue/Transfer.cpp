#include "Transfer.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::queue{

//Constructor / Destructor
Transfer::Transfer(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

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

  //Save thread information
  vk_struct->profiler->prf_vulkan->add_thread("Transfer queue");

  //Start thread loop
  this->thread_running = true;
  while(thread_running){
    this->wait_for_command();
    this->process_command();
  }

  //---------------------------
}
void Transfer::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Transfer::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Command
void Transfer::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  while((vec_command_prepa.empty() || vk_struct->queue.standby) && thread_running){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Transfer::add_command(vk::structure::Command_buffer* command){
  mutex.lock();
  //---------------------------

  if(command->is_recorded){
    vec_command_prepa.push_back(command);
  }

  //---------------------------
  this->thread_idle = false;
  mutex.unlock();
}
void Transfer::process_command(){
  if(!thread_running) return;
  //---------------------------

  this->build_submission();
  this->make_submission();
  this->post_submission();

  //---------------------------
}

//Submission
void Transfer::build_submission(){
  //---------------------------

  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();

  for(int i=0; i<vec_command_onrun.size(); i++){
    this->vec_command_buffer.push_back(vec_command_onrun[i]->command);
  }

  //---------------------------
}
void Transfer::make_submission(){
  this->thread_idle = false;
  //---------------------------

  vk::structure::Fence* fence = vk_fence->query_free_fence();

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  VkQueue queue = vk_struct->device.queue.transfer.handle;
  VkResult result = vkQueueSubmit(queue, 1, &submit_info, fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] graphics queue submission");
  }
  if(result == VK_TIMEOUT){
    throw std::runtime_error("[error] graphics queue submission timeout");
  }

  vkWaitForFences(vk_struct->device.handle, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
  this->thread_idle = true;
}
void Transfer::post_submission(){
  //---------------------------

  //Reset command buffer
  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command_buffer* command_buffer = vec_command_onrun[i];

    if(command_buffer->is_resetable){
      command_buffer->is_available = true;
      command_buffer->is_recorded = false;
      command_buffer->query.is_in_use = false;
    }
  }

  this->vec_command_onrun.clear();
  this->vec_command_buffer.clear();

  //---------------------------
}

}
