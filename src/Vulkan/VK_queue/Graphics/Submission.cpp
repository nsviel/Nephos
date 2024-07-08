#include "Submission.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::queue::graphics{

//Constructor / Destructor
Submission::Submission(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

  //---------------------------

}
Submission::~Submission(){}

//Main function
void Submission::process_command(std::vector<vk::structure::Command*> vec_command, bool with_presentation){
  //---------------------------

  //Submission stuff
  VkSemaphore semaphore;
  std::vector<VkSubmitInfo> vec_info;
  this->build_submission(vec_command, vec_info, semaphore);
  this->make_submission(vec_info);
  this->post_submission(vec_command);

  //If required, make image presentation
  if(with_presentation){
    //vk_struct->queue.presentation->image_presentation(semaphore);
  }

  //---------------------------
}

//Subfunction
void Submission::build_submission(std::vector<vk::structure::Command*> vec_command, std::vector<VkSubmitInfo>& vec_info, VkSemaphore& semaphore){
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
void Submission::make_submission(std::vector<VkSubmitInfo>& vec_info){
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
void Submission::post_submission(std::vector<vk::structure::Command*> vec_command){
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
