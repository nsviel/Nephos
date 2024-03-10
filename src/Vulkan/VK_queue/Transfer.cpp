#include "Transfer.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::queue{

//Constructor / Destructor
Transfer::Transfer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_query = new vk::instance::Query(struct_vulkan);

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
  struct_vulkan->profiler->prf_vulkan->add_thread("Transfer queue");

  //Start thread loop
  this->thread_running = true;
  while(thread_running){
    this->wait_for_command();
    this->prepare_submission();
    this->queue_submission();
    this->post_submission();
  }

  //---------------------------
}
void Transfer::add_command(vk::structure::Command_buffer* command){
  //---------------------------

  if(command->is_recorded){
    vec_command_prepa.push_back(command);
  }

  //---------------------------
}

//Subfunction
void Transfer::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  this->queue_idle = true;

  while(vec_command_prepa.empty() || struct_vulkan->queue.standby){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  this->queue_idle = false;

  //---------------------------
}
void Transfer::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(queue_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Transfer::prepare_submission(){
  //---------------------------

  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();

  for(int i=0; i<vec_command_onrun.size(); i++){
    this->vec_command_buffer.push_back(vec_command_onrun[i]->command);
  }

  //---------------------------
}
void Transfer::queue_submission(){
  //---------------------------

  vk::structure::Fence* fence = vk_fence->query_free_fence();

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  VkQueue queue = struct_vulkan->device.queue.transfer.handle;
  VkResult result = vkQueueSubmit(queue, 1, &submit_info, fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] graphics queue submission");
  }
  if(result == VK_TIMEOUT){
    throw std::runtime_error("[error] graphics queue submission timeout");
  }

  vkWaitForFences(struct_vulkan->device.handle, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Transfer::post_submission(){
  //---------------------------

  //Reset command buffer
  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command_buffer* command_buffer = vec_command_onrun[i];

    if(command_buffer->is_resetable){
      vkResetCommandBuffer(command_buffer->command, 0);
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
