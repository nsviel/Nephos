#include "VK_submit.h"

#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_presentation/VK_swapchain.h>
#include <VK_presentation/VK_surface.h>
#include <VK_data/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>


//Constructor / Destructor
VK_submit::VK_submit(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_swapchain = new VK_swapchain(struct_vulkan);
  this->vk_surface = new VK_surface(struct_vulkan);

  //---------------------------
}
VK_submit::~VK_submit(){}

//Main function
void VK_submit::acquire_next_image(Struct_swapchain* swapchain, VkSemaphore& semaphore, VkFence& fence){
  //---------------------------

  //Wait and reset fence
  vkWaitForFences(struct_vulkan->device.device, 1, &fence, VK_TRUE, UINT64_MAX);
  vkResetFences(struct_vulkan->device.device, 1, &fence);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(struct_vulkan->device.device, swapchain->swapchain, UINT64_MAX, semaphore, VK_NULL_HANDLE, &swapchain->frame_presentation_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //Window resizing
  vk_surface->check_for_resizing();
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //---------------------------
}
void VK_submit::set_next_frame_ID(Struct_swapchain* swapchain){
  //---------------------------

  int current_ID = swapchain->frame_presentation_ID;
  current_ID = (current_ID + 1) % struct_vulkan->instance.max_frame_inflight;
  swapchain->frame_presentation_ID = current_ID;

  //---------------------------
}

//Queue submission
void VK_submit::submit_command_graphics(VkCommandBuffer command){
  //---------------------------

  VkSubmitInfo end_info = {};
  end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  end_info.commandBufferCount = 1;
  end_info.pCommandBuffers = &command;
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &end_info, VK_NULL_HANDLE);
  if(result != VK_SUCCESS){
    throw std::runtime_error("gui font error");
  }

  //---------------------------
}
void VK_submit::submit_command_render(Struct_command* command){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = command->vec_semaphore_wait.size();
  submit_info.pWaitSemaphores = command->vec_semaphore_wait.data();
  submit_info.pWaitDstStageMask = command->vec_wait_stage.data();
  submit_info.signalSemaphoreCount = command->vec_semaphore_done.size();
  submit_info.pSignalSemaphores = command->vec_semaphore_done.data();
  submit_info.commandBufferCount = command->vec_command_buffer.size();
  submit_info.pCommandBuffers = command->vec_command_buffer.data();

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, command->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_submit::submit_presentation(Struct_swapchain* swapchain, VkSemaphore& semaphore){
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
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || struct_vulkan->window.is_resized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}
