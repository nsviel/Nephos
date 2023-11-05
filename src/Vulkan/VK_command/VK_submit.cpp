#include "VK_submit.h"
#include "../VK_pipeline/VK_pipeline.h"
#include <VK_main/VK_engine.h>
#include "../VK_struct/struct_vulkan.h"
#include "../VK_presentation/VK_swapchain.h"
#include "../VK_presentation/VK_surface.h"
#include "../VK_presentation/VK_canvas.h"
#include "../VK_binding/VK_descriptor.h"


//Constructor / Destructor
VK_submit::VK_submit(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->vk_surface = vk_engine->get_vk_surface();

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
  VkResult result = vkAcquireNextImageKHR(struct_vulkan->device.device, swapchain->swapchain, UINT64_MAX, semaphore, VK_NULL_HANDLE, &swapchain->frame_current_ID);
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

  int current_ID = swapchain->frame_current_ID;
  current_ID = (current_ID + 1) % struct_vulkan->instance.max_frame_inflight;
  swapchain->frame_current_ID = current_ID;

  //---------------------------
}

//Queue submission
void VK_submit::submit_graphics_command(Struct_submit_command* command){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores = &command->semaphore_wait;
  submit_info.pWaitDstStageMask = &command->wait_stage;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = &command->semaphore_done;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command->command_buffer;

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, command->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_submit::submit_graphics_command(Struct_renderpass* renderpass){
  //---------------------------

  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_wait = renderpass->semaphore_wait;
  command.semaphore_done = renderpass->semaphore_done;
  command.fence = renderpass->fence;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores  = &command.semaphore_wait;
  submit_info.pWaitDstStageMask = &command.wait_stage;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = &command.semaphore_done;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command.command_buffer;

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, command.fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_submit::submit_graphics_commands(Struct_submit_commands* commands){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = commands->vec_semaphore_rp_wait.size();
  submit_info.pWaitSemaphores = commands->vec_semaphore_rp_wait.data();
  submit_info.pWaitDstStageMask = commands->vec_wait_stage.data();
  submit_info.signalSemaphoreCount = commands->vec_semaphore_render.size();
  submit_info.pSignalSemaphores = commands->vec_semaphore_render.data();
  submit_info.commandBufferCount = commands->vec_command_buffer.size();
  submit_info.pCommandBuffers = commands->vec_command_buffer.data();

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submit_info, commands->fence);
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
  presentation_info.pImageIndices = &swapchain->frame_current_ID;
  presentation_info.pResults = nullptr; // Optional

  VkResult result = vkQueuePresentKHR(struct_vulkan->device.queue_presentation, &presentation_info);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || struct_vulkan->window.is_resized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}
