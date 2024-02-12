#include "Presentation.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Presentation::Presentation(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_swapchain = new Swapchain(struct_vulkan);
  this->vk_surface = new Surface(struct_vulkan);

  //---------------------------
}
Presentation::~Presentation(){}

//Main function
void Presentation::acquire_next_image(VkSemaphore& semaphore){
  vk::structure::Swapchain* swapchain = &struct_vulkan->swapchain;
  //---------------------------

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(struct_vulkan->device.device, swapchain->swapchain, UINT64_MAX, semaphore, VK_NULL_HANDLE, &swapchain->frame_presentation_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapchain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //---------------------------
}
void Presentation::image_presentation(VkSemaphore& semaphore, vk::structure::Fence* fence){
  //---------------------------


  this->submit_presentation(semaphore);
  this->next_frame_ID();



  //---------------------------
}

//Subfunction
void Presentation::submit_presentation(VkSemaphore& semaphore){
  vk::structure::Swapchain* swapchain = &struct_vulkan->swapchain;
  //---------------------------

  VkPresentInfoKHR presentation_info{};
  presentation_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentation_info.waitSemaphoreCount = 1;
  presentation_info.pWaitSemaphores = &semaphore;
  presentation_info.swapchainCount = 1;
  presentation_info.pSwapchains = &swapchain->swapchain;
  presentation_info.pImageIndices = &swapchain->frame_presentation_ID;
  presentation_info.pResults = nullptr; // Optional

  VkResult result = vkQueuePresentKHR(struct_vulkan->device.queue_presentation, &presentation_info);

  //Window resizing
  vk_surface->check_for_resizing();
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || struct_vulkan->window.is_resized){
    vk_swapchain->recreate_swapchain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}
void Presentation::next_frame_ID(){
  vk::structure::Swapchain* swapchain = &struct_vulkan->swapchain;
  //---------------------------

  int current_ID = swapchain->frame_presentation_ID;
  current_ID = (current_ID + 1) % struct_vulkan->instance.max_frame_inflight;
  swapchain->frame_presentation_ID = current_ID;

  //---------------------------
}

}
