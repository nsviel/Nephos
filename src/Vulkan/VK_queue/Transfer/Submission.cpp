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
}
Submission::~Submission(){}

//Main function
void Submission::process_command(vk::structure::Command_buffer* command){
  //---------------------------

  std::vector<VkSubmitInfo> vec_info;
  this->build_submission(command, vec_info);
  this->make_submission(vec_info);
  this->post_submission(command);

  //---------------------------
}

//Submission
void Submission::build_submission(vk::structure::Command_buffer* command, std::vector<VkSubmitInfo>& vec_info){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command->handle;

  vec_info.push_back(submit_info);

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
void Submission::post_submission(vk::structure::Command_buffer* command){
  //---------------------------

  std::lock_guard<std::mutex> lock(command->mutex);
  if(command->is_resetable){
    command->is_recorded = false;
    command->query.is_available = true;
    command->is_available = true;
  }

  //---------------------------
}

}
