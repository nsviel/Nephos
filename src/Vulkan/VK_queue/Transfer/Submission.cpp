#include "Submission.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace vk::queue::transfer{

//Constructor / Destructor
Submission::Submission(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_query = new vk::instance::Query(vk_struct);

  //---------------------------
  this->start_thread();
}
Submission::~Submission(){}

//Main function
void Submission::process_command(std::vector<vk::structure::Command_buffer*> vec_command){
  //---------------------------

  std::vector<VkSubmitInfo> vec_info;
  this->build_submission(vec_command, vec_info);
  this->make_submission(vec_info);
  this->post_submission(vec_command);

  //---------------------------
}

//Submission
void Submission::build_submission(std::vector<vk::structure::Command_buffer*> vec_command, std::vector<VkSubmitInfo>& vec_info){
  //---------------------------

  for(int i=0; i<vec_command.size(); i++){
    VkSubmitInfo submit_info{};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &vec_command[i]->handle;

    vec_info.push_back(submit_info);
  }

  //---------------------------
}
void Submission::make_submission(std::vector<VkSubmitInfo>& vec_info){

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
void Submission::post_submission(std::vector<vk::structure::Command_buffer*> vec_command){
  //---------------------------
  //say("-----");
  //Reset command buffer
  for(int i=0; i<vec_command.size(); i++){
    vk::structure::Command_buffer* command_buffer = vec_command[i];

    //say(command_buffer->handle);
    std::lock_guard<std::mutex> lock(command_buffer->mutex);
    if(command_buffer->is_resetable){
      command_buffer->is_recorded = false;
      command_buffer->query.is_available = true;
      command_buffer->is_available = true;
    }
  }
  vec_command.clear();

  //---------------------------
}

}
