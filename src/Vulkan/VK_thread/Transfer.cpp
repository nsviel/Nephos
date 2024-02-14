#include "Transfer.h"

#include <Vulkan/Namespace.h>
#include <thread>


namespace vk::thread{

//Constructor / Destructor
Transfer::Transfer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Transfer::~Transfer(){}

//Main functions
void Transfer::submitToTransferQueue(VkDevice device, VkQueue transferQueue){
  //---------------------------
/*
  // Your command buffer submission code goes here
  // For example:
  VkCommandBuffer commandBuffer; // Assuming you have a command buffer prepared
  VkSubmitInfo submitInfo = {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  // Submit the command buffer to the transfer queue
  vkQueueSubmit(struct_vulkan, 1, &submitInfo, VK_NULL_HANDLE);
  std::cout << "Command submitted to transfer queue" << std::endl;
*/
  //---------------------------
}

}
