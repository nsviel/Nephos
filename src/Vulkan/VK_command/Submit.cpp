#include "Submit.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Submit::Submit(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Submit::~Submit(){}

//Main function
void Submit::submit_command_graphics(VkCommandBuffer command){
  //---------------------------

  VkSubmitInfo submit_info = {};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command;
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, VK_NULL_HANDLE);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  //---------------------------
}
void Submit::submit_command_render(vk::structure::Command* command){
  //---------------------------

  vector<VkCommandBuffer> vec_command_buffer;
  for(int i=0; i<command->vec_command_buffer.size(); i++){
    vec_command_buffer.push_back(command->vec_command_buffer[i].command);
  }

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = command->vec_semaphore_wait.size();
  submit_info.pWaitSemaphores = command->vec_semaphore_wait.data();
  submit_info.pWaitDstStageMask = command->vec_wait_stage.data();
  submit_info.signalSemaphoreCount = command->vec_semaphore_done.size();
  submit_info.pSignalSemaphores = command->vec_semaphore_done.data();
  submit_info.commandBufferCount = vec_command_buffer.size();
  submit_info.pCommandBuffers = vec_command_buffer.data();

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, command->fence);

  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}

}
