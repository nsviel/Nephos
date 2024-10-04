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
void Submission::process_command(std::shared_ptr<vk::structure::Command_set> set){
  //---------------------------

  this->build_submission(set);
  this->make_submission(set);
  this->post_submission(set);

  //---------------------------
}

//Subfunction
void Submission::build_submission(std::shared_ptr<vk::structure::Command_set> set){
  //---------------------------

  vec_info.clear();
  for(auto& command: set->vec_command){
    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    //Semaphore wait
    if(command->semaphore_wait != VK_NULL_HANDLE){
      submit_info.waitSemaphoreCount = 1;
      submit_info.pWaitSemaphores = &command->semaphore_wait;
    }

    //Semaphore done
    if(command->semaphore_done != VK_NULL_HANDLE){
      submit_info.pSignalSemaphores = &command->semaphore_done;
      submit_info.signalSemaphoreCount = 1;
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
void Submission::make_submission(std::shared_ptr<vk::structure::Command_set> set){
  //---------------------------

  //auto fence = vk_fence->query_free_fence();

  VkQueue queue = vk_struct->core.device.queue.graphics.handle;
  VkResult result = vkQueueSubmit(queue, vec_info.size(), vec_info.data(), set->fence->handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  vk_fence->wait_fence(*set->fence);

  //---------------------------
}
void Submission::post_submission(std::shared_ptr<vk::structure::Command_set> set){
  //---------------------------

  //Reset all command
  for(auto& command : set->vec_command){
    // Command buffer timestamp
    vk_query->find_query_timestamp(*command->command_buffer);

    // Command buffer reset
    if(command->command_buffer->is_resetable){
      command->command_buffer->is_recorded = false;
      command->command_buffer->query.is_available = true;
      command->command_buffer->is_available = true;
    }
  }
  set->vec_command.clear();

  set->mark_as_done();

  //---------------------------
}


}
