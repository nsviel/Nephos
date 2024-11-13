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
void Submission::process_command(vk::structure::Command_buffer& command_buffer){
  //---------------------------

  std::vector<VkSubmitInfo> vec_info;
  this->build_submission(command_buffer, vec_info);
  this->make_submission(vec_info);
  this->post_submission(command_buffer);

  //---------------------------
}

//Submission
void Submission::build_submission(vk::structure::Command_buffer& command_buffer, std::vector<VkSubmitInfo>& vec_info){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command_buffer.handle;

  vec_info.push_back(submit_info);

  //---------------------------
}
void Submission::make_submission(std::vector<VkSubmitInfo>& vec_info){
  //---------------------------

  auto fence = vk_fence->query_free_fence();

  VkQueue queue = vk_struct->core.device.queue.transfer.handle;
  VkResult result = vkQueueSubmit(queue, vec_info.size(), vec_info.data(), fence->handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] graphics queue submission");
  }
  if(result == VK_TIMEOUT){
    throw std::runtime_error("[error] graphics queue submission timeout");
  }

  vk_fence->wait_fence(*fence);

  //---------------------------
}
void Submission::post_submission(vk::structure::Command_buffer& command_buffer){
  //---------------------------

  std::lock_guard<std::mutex> lock(command_buffer.mutex);
  if(command_buffer.is_resetable){
    command_buffer.is_recorded = false;
    command_buffer.query.is_available = true;
    command_buffer.is_available = true;
  }

  //---------------------------
}

}
