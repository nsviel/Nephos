#include "Presentation.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Presentation::Presentation(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);

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
  if(vk_window->is_window_resized()){
    vk_swapchain->recreate_swapchain();
    return false;
  }
  VkResult result = vkAcquireNextImageKHR(vk_struct->device.handle, swapchain->handle, UINT64_MAX, semaphore, VK_NULL_HANDLE, &swapchain->current_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapchain();
    return false;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
    return false;
  }

  //---------------------------
  return true;
}
void Presentation::image_presentation(VkSemaphore& semaphore){
  this->thread_idle = false;
  //---------------------------

  this->submit_presentation(semaphore);
  this->next_frame_ID();

  //---------------------------
  this->thread_idle = true;
}
void Presentation::add_presentation_command(std::vector<vk::structure::Command*> vec_command){
  //---------------------------

  vk::structure::Command* command = vec_command[vec_command.size() - 1];
  VkSemaphore& semaphore = command->semaphore_done;



  vk_struct->queue.graphics->add_presentation(vec_command);
  //vk_struct->queue.graphics->wait_for_idle();
  //this->image_presentation(semaphore);

  //---------------------------
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
  presentation_info.pSwapchains = &swapchain->handle;
  presentation_info.pImageIndices = &swapchain->current_ID;
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

  int current_ID = swapchain->current_ID;
  current_ID = (current_ID + 1) % vk_struct->instance.max_frame_inflight;
  swapchain->current_ID = current_ID;

  //---------------------------
}

}