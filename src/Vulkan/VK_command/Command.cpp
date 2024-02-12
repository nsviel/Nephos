#include "Command.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command::Command(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Command::~Command(){}

//Main function
void Command::submit_command(vk::structure::Command* command){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = command->vec_semaphore_processing.size();
  submit_info.pWaitSemaphores = command->vec_semaphore_processing.data();
  submit_info.pWaitDstStageMask = command->vec_wait_stage.data();
  submit_info.signalSemaphoreCount = command->vec_semaphore_done.size();
  submit_info.pSignalSemaphores = command->vec_semaphore_done.data();
  submit_info.commandBufferCount = command->vec_command_buffer.size();
  submit_info.pCommandBuffers = command->vec_command_buffer.data();

  VkFence fence = VK_NULL_HANDLE;
  if(command->fence != nullptr){
    fence = command->fence->fence;
  }

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, fence);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] command buffer queue submission");
  }

  //---------------------------
}

}
