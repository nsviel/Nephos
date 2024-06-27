#include "Transfer.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::queue{

//Constructor / Destructor
Transfer::Transfer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

  //---------------------------
  this->start_thread();
}
Transfer::~Transfer(){}

//Main function
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
  vk_struct->device.queue.transfer.type = vk::queue::TRANSFER;
  vk_struct->device.queue.transfer.thread_ID = utl::thread::get_ID_str();

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
  mutex.unlock();
}
void Transfer::process_command(){
  if(!thread_running) return;
  //---------------------------

  //Passing the command torch
  mutex.lock();
  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();
  mutex.unlock();

  //Submission stuff
  vector<VkSubmitInfo> vec_info;
  this->build_submission(vec_info);
  this->make_submission(vec_info);
  this->post_submission();

  //---------------------------
}

//Submission
void Transfer::build_submission(std::vector<VkSubmitInfo>& vec_info){
  //---------------------------

  for(int i=0; i<vec_command_onrun.size(); i++){
    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &vec_command_onrun[i]->handle;

    vec_info.push_back(submit_info);
  }

  //---------------------------
}
void Transfer::make_submission(std::vector<VkSubmitInfo>& vec_info){
  this->thread_idle = false;
  //---------------------------

  vk::synchro::structure::Fence* fence = vk_fence->query_free_fence();

  VkQueue queue = vk_struct->device.queue.transfer.handle;
  VkResult result = vkQueueSubmit(queue, vec_info.size(), vec_info.data(), fence->handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] graphics queue submission");
  }
  if(result == VK_TIMEOUT){
    throw std::runtime_error("[error] graphics queue submission timeout");
  }

  vkWaitForFences(vk_struct->device.handle, 1, &fence->handle, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Transfer::post_submission(){
  //---------------------------
  //say("-----");
  //Reset command buffer
  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command_buffer* command_buffer = vec_command_onrun[i];

    //say(command_buffer->handle);
    std::lock_guard<std::mutex> lock(command_buffer->mutex);
    if(command_buffer->is_resetable){
      command_buffer->is_recorded = false;
      command_buffer->query.is_available = true;
      command_buffer->is_available = true;
    }
  }
  this->vec_command_onrun.clear();

  //---------------------------
  this->thread_idle = true;
}

}
