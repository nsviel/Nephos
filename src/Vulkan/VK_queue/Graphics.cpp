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
void Graphics::add_command(vk::structure::Command* command){
  //---------------------------

  vec_command_prepa.push_back(command);

  //this->wait_for_command();
  this->reset_for_submission();
  this->prepare_submission();
  this->queue_submission();
  this->post_submission();

  //---------------------------
}
void Graphics::add_command_thread(vk::structure::Command_buffer* command_buffer){
  //---------------------------

  vk::structure::Command* command = new vk::structure::Command();
  command->vec_command_buffer.push_back(command_buffer);
  vec_command_prepa.push_back(command);

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

//WORK IN PROGRESS
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
void Graphics::add_command(vector<vk::structure::Command*> vec_command, bool with_presentation){
  //---------------------------

  vec_command_prepa = vec_command;
  this->queue_idle = false;
  this->with_presentation = with_presentation;


  //---------------------------
}
void Graphics::process_command(){
  //---------------------------

  this->vec_command_onrun = vec_command_prepa;
  this->vec_command_prepa.clear();


  vk::structure::Fence* fence = vk_fence->query_free_fence();

  VkSemaphore semaphore_done;
  vector<VkSubmitInfo> vec_info;
  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = &command->vec_semaphore_processing[0];
    submit_info.pWaitDstStageMask = &command->vec_wait_stage[0];
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = &command->vec_semaphore_done[0];
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command->vec_command_buffer[0]->command;

    semaphore_done = command->vec_semaphore_done[0];

    vec_info.push_back(submit_info);
  }



  VkQueue queue = vk_struct->device.queue.graphics.handle;
  VkResult result = vkQueueSubmit(queue, vec_info.size(), vec_info.data(), fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vkWaitForFences(vk_struct->device.handle, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);


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



    vk_struct->queue.presentation->image_presentation(semaphore_done);

  //---------------------------
  this->queue_idle = true;
}

//Subfunction
void Graphics::wait_for_command(){
  //For internal thread to wait for to submit commands
  //---------------------------



  //IF FAUT TOUT METTRE DANS LE QUEUE THREAD
//say("graphics off");
  while(vec_command_prepa.empty() || vk_struct->queue.standby){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

//say("graphics on");


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

  VkQueue queue = vk_struct->device.queue.graphics.handle;
  VkResult result = vkQueueSubmit(queue, 1, &submit_info, fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vkWaitForFences(vk_struct->device.handle, 1, &fence->fence, VK_TRUE, UINT64_MAX);
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

  //---------------------------
}

}
