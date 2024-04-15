#include "Presentation.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Presentation::Presentation(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);

  //---------------------------
}
Presentation::~Presentation(){}

//Main function
void Presentation::wait_for_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}
bool Presentation::acquire_next_image(VkSemaphore& semaphore){
  vk::structure::Swapchain* swapchain = &vk_struct->swapchain;
  //---------------------------

  //Acquiring an image from the swap chain
  if(check_for_resizing()) return false;
  VkResult result = vkAcquireNextImageKHR(vk_struct->device.handle, swapchain->swapchain, UINT64_MAX, semaphore, VK_NULL_HANDLE, &swapchain->frame_presentation_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){say("out of date");
    vk_swapchain->recreate_swapchain();
    return false;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
    return false;
  }

  //---------------------------
  return true;
}
bool Presentation::check_for_resizing(){
  vk::structure::Swapchain* swapchain = &vk_struct->swapchain;
  //---------------------------

  vk_surface->check_for_resizing();
  if(vk_struct->window.resized){
    vk_swapchain->recreate_swapchain();
    return true;
  }

  //---------------------------
  return false;
}
void Presentation::image_presentation(VkSemaphore& semaphore){
  this->thread_idle = false;
  //---------------------------

  this->submit_presentation(semaphore);
  this->next_frame_ID();

  //---------------------------
  this->thread_idle = true;
}

//Subfunction
void Presentation::submit_presentation(VkSemaphore& semaphore){
  vk::structure::Swapchain* swapchain = &vk_struct->swapchain;
  //---------------------------

  VkPresentInfoKHR presentation_info{};
  presentation_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentation_info.waitSemaphoreCount = 1;
  presentation_info.pWaitSemaphores = &semaphore;
  presentation_info.swapchainCount = 1;
  presentation_info.pSwapchains = &swapchain->swapchain;
  presentation_info.pImageIndices = &swapchain->frame_presentation_ID;
  presentation_info.pResults = nullptr; // Optional

  VkQueue queue = vk_struct->device.queue.presentation.handle;
  VkResult result = vkQueuePresentKHR(queue, &presentation_info);

  //Window resizing
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR){
    //this->thread_idle = true;
    //vk_swapchain->recreate_swapchain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}
void Presentation::next_frame_ID(){
  vk::structure::Swapchain* swapchain = &vk_struct->swapchain;
  //---------------------------

  int current_ID = swapchain->frame_presentation_ID;
  current_ID = (current_ID + 1) % vk_struct->instance.max_frame_inflight;
  swapchain->frame_presentation_ID = current_ID;

  //---------------------------
}

}
