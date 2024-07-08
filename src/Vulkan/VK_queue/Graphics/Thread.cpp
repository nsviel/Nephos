#include "Thread.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::graphics{

//Constructor / Destructor
Thread::Thread(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);
  this->vk_submission = new vk::queue::graphics::Submission(vk_struct);

  //---------------------------
  this->start_thread();

}
Thread::~Thread(){}

//Main function
void Thread::thread_init(){
  //---------------------------

  vk_struct->device.queue.graphics.type = vk::queue::GRAPHICS;
  vk_struct->device.queue.graphics.thread_ID = utl::thread::get_ID_str();
  vk_struct->device.queue.presentation.type = vk::queue::PRESENTATION;
  vk_struct->device.queue.presentation.thread_ID = utl::thread::get_ID_str();

  //---------------------------
}
void Thread::thread_loop(){
  //---------------------------

  this->wait_for_command();

  //Passing the command torch
  mutex.lock();
  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();
  mutex.unlock();

  this->thread_idle = false;
  this->process_command(vec_command_onrun);
  this->thread_idle = true;

  //---------------------------
}

//Subfunction
void Thread::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------

  while((vec_command_prepa.empty()) && thread_running){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Thread::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Thread::process_command(std::vector<vk::structure::Command*> vec_command){
  //---------------------------

  //Submission stuff
  VkSemaphore semaphore;
  std::vector<VkSubmitInfo> vec_info;
  this->build_submission(vec_command, vec_info, semaphore);
  this->make_submission(vec_info);
  this->post_submission(vec_command);

  //If required, make image presentation
  if(with_presentation){
    vk_struct->queue.presentation->image_presentation(semaphore);
  }

  //---------------------------
}

//Command
void Thread::add_command(vk::structure::Command* command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  this->wait_for_idle();

  mutex.lock();
  this->thread_idle = false;
  this->with_presentation = false;
  vec_command_prepa.push_back(command);
  mutex.unlock();

  //---------------------------
}
void Thread::add_graphics(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  this->wait_for_idle();

  mutex.lock();
  this->thread_idle = false;
  this->with_presentation = false;
  vec_command_prepa = vec_command;
  mutex.unlock();

  //---------------------------

}
void Thread::add_presentation(std::vector<vk::structure::Command*> vec_command){
  if(vk_struct->queue.standby) return;
  //---------------------------

  this->wait_for_idle();

  mutex.lock();
  this->thread_idle = false;
  this->with_presentation = true;
  vec_command_prepa = vec_command;
  mutex.unlock();

  //---------------------------
}

//Submission
void Thread::build_submission(std::vector<vk::structure::Command*> vec_command, std::vector<VkSubmitInfo>& vec_info, VkSemaphore& semaphore){
  //---------------------------

  for(int i=0; i<vec_command.size(); i++){
    vk::structure::Command* command = vec_command[i];

    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    //Semaphore wait
    if(command->semaphore_wait != VK_NULL_HANDLE){
      submit_info.waitSemaphoreCount = 1;
      submit_info.pWaitSemaphores = &command->semaphore_wait;
    }

    //Semaphore done
    if(command->semaphore_done != VK_NULL_HANDLE){
      submit_info.signalSemaphoreCount = 1;
      submit_info.pSignalSemaphores = &command->semaphore_done;

      semaphore = command->semaphore_done;
    }

    //Pipeline wait stage
    if(command->wait_stage != 0){
      submit_info.pWaitDstStageMask = &command->wait_stage;
    }

    //Command buffer
    if(command->command_buffer->handle != VK_NULL_HANDLE){
      submit_info.commandBufferCount = 1;
      submit_info.pCommandBuffers = &command->command_buffer->handle;
    }else{
      std::cout<<"[error] command buffer is VK_NULL"<<std::endl;
    }

    vec_info.push_back(submit_info);
  }

  //---------------------------
}
void Thread::make_submission(std::vector<VkSubmitInfo>& vec_info){
  //---------------------------

  vk::synchro::structure::Fence* fence = vk_fence->query_free_fence();

  VkQueue queue = vk_struct->device.queue.graphics.handle;
  VkResult result = vkQueueSubmit(queue, vec_info.size(), vec_info.data(), fence->handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vkWaitForFences(vk_struct->device.handle, 1, &fence->handle, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Thread::post_submission(std::vector<vk::structure::Command*> vec_command){
  //---------------------------

  //Reset all command
  for(int i=0; i<vec_command.size(); i++){
    vk::structure::Command* command = vec_command[i];

    //Command buffer timestamp
    vk_query->find_query_timestamp(command->command_buffer);

    //Command buffer reset
    if(command->command_buffer->is_resetable){
      command->command_buffer->is_recorded = false;
      command->command_buffer->query.is_available = true;
      command->command_buffer->is_available = true;
    }

    delete command;
  }

  //---------------------------
}


}
