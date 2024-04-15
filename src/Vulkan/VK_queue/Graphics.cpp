#include "Graphics.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Graphics::Graphics(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

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

  //Save thread information
  vk_struct->profiler->prf_vulkan->add_thread("Graphics queue");

  //Start thread loop
  this->thread_running = true;
  while(thread_running){
    this->wait_for_command();
    this->process_command();
  }

  //---------------------------
}
void Graphics::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Processing
void Graphics::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Graphics::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  while((vec_command_prepa.empty() || vk_struct->queue.standby) && thread_running){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Graphics::process_command(){
  if(!thread_running) return;
  //---------------------------

  //Passing the command torch
  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();

  //Submission stuff
  VkSemaphore flag;
  vector<VkSubmitInfo> vec_info;
  this->build_submission(vec_info, flag);
  this->make_submission(vec_info);
  this->post_submission(flag);

  //---------------------------
}

//Command
void Graphics::add_command(vk::structure::Command* command){
  mutex.lock();
  //---------------------------

  this->wait_for_idle();
  vec_command_prepa.push_back(command);
  this->thread_idle = false;
  this->with_presentation = false;

  //---------------------------
  mutex.unlock();
}
void Graphics::add_graphics(vector<vk::structure::Command*> vec_command){
  mutex.lock();
  //---------------------------

  this->wait_for_idle();
  vec_command_prepa = vec_command;
  this->thread_idle = false;
  this->with_presentation = false;

  //---------------------------
  mutex.unlock();
}
void Graphics::add_presentation(vector<vk::structure::Command*> vec_command){
  mutex.lock();
  //---------------------------

  this->wait_for_idle();
  vec_command_prepa = vec_command;
  this->thread_idle = false;
  this->with_presentation = true;

  //---------------------------
  mutex.unlock();
}

//Submission
void Graphics::build_submission(vector<VkSubmitInfo>& vec_info, VkSemaphore& done){
  //---------------------------

  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    if(command->vec_semaphore_processing.size() > 0){
      submit_info.waitSemaphoreCount = 1;
      submit_info.pWaitSemaphores = &command->vec_semaphore_processing[0];
    }

    if(command->vec_wait_stage.size() > 0){
      submit_info.pWaitDstStageMask = &command->vec_wait_stage[0];
    }

    if(command->vec_semaphore_done.size() > 0){
      submit_info.signalSemaphoreCount = 1;
      submit_info.pSignalSemaphores = &command->vec_semaphore_done[0];

      done = command->vec_semaphore_done[0];
    }

    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command->vec_command_buffer[0]->command;

    vec_info.push_back(submit_info);
  }

  //---------------------------
}
void Graphics::make_submission(vector<VkSubmitInfo>& vec_info){
  this->thread_idle = false;
  //---------------------------

  vk::structure::Fence* fence = vk_fence->query_free_fence();

  VkQueue queue = vk_struct->device.queue.graphics.handle;
  VkResult result = vkQueueSubmit(queue, vec_info.size(), vec_info.data(), fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vkWaitForFences(vk_struct->device.handle, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Graphics::post_submission(VkSemaphore& semaphore_done){
  //---------------------------

  //Reset all command buffers
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

  //If required, make image presentation
  if(with_presentation){
    vk_struct->queue.presentation->image_presentation(semaphore_done);
  }

  //---------------------------
  this->thread_idle = true;
}


}
