#include "Presentation.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::queue{

//Constructor / Destructor
Presentation::Presentation(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);

  //---------------------------
  this->start_thread();
}
Presentation::~Presentation(){}

//Main functions
void Presentation::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Presentation::run_thread, this);
  }

  //---------------------------
}
void Presentation::run_thread(){
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
void Presentation::add_command(vk::structure::Command* command){
  //---------------------------

  vec_command_prepa.push_back(command);

  //---------------------------
}

//Subfunction
void Presentation::wait_for_command(){
  //---------------------------

  while(vec_command_prepa.empty()){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
void Presentation::reset_for_submission(){
  //---------------------------

  this->vec_command_buffer.clear();
  this->vec_semaphore_processing.clear();
  this->vec_semaphore_done.clear();
  this->vec_wait_stage.clear();

  //---------------------------
}
void Presentation::prepare_submission(){
  //---------------------------

  for(int i=0; i<vec_command_onrun.size(); i++){
    vk::structure::Command* command = vec_command_onrun[i];

    //Command buffer
    for(int i=0; i<command->vec_command_buffer.size(); i++){
      vk::structure::Command_buffer* command_buffer = command->vec_command_buffer[i];
      this->vec_command_buffer.push_back(command_buffer->command);
    }

    //Synchro stuff
    this->vec_semaphore_processing = command->vec_semaphore_processing;
    this->vec_wait_stage = command->vec_wait_stage;
    this->vec_semaphore_done = command->vec_semaphore_done;
  }

  //---------------------------
}
void Presentation::queue_submission(){
  //---------------------------

  vk::structure::Fence* fence = vk_fence->query_free_fence();

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  VkResult result = vkQueueSubmit(struct_vulkan->device.queue.presentation, 1, &submit_info, fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vkWaitForFences(struct_vulkan->device.device, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_fence->reset_fence(fence);

  //---------------------------
}
void Presentation::post_submission(){
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
  }

  this->vec_command_onrun.clear();
  this->vec_command_buffer.clear();

  //---------------------------
}

}