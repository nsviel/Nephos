#include "Submission.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Submission::Submission(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_recorder = new vk::draw::Recorder(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);

  //---------------------------
}
Submission::~Submission(){}

//Main function
void Submission::submit_rendering(vk::structure::Render& render){
  //---------------------------

  vk::commandbuffer::structure::Set* set = new vk::commandbuffer::structure::Set();
  set->vec_command = std::move(render.vec_command);
  set->semaphore = render.semaphore->handle;
  set->supress = false;
  vk_struct->core.queue.graphics->add_command(set);
  set->wait_until_done();
  delete set;

  //---------------------------
}
void Submission::submit_presentation(vk::structure::Render& render){
  vk::structure::Swapchain& swapchain = vk_struct->core.swapchain;
  //---------------------------

  VkPresentInfoKHR presentation_info{};
  presentation_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentation_info.waitSemaphoreCount = 1;
  presentation_info.pWaitSemaphores = &render.semaphore->handle;
  presentation_info.swapchainCount = 1;
  presentation_info.pSwapchains = &swapchain.handle;
  presentation_info.pImageIndices = &swapchain.current_ID;
  presentation_info.pResults = nullptr; // Optional

  VkQueue queue = vk_struct->core.device.queue.presentation.handle;
  VkResult result = vkQueuePresentKHR(queue, &presentation_info);

  //Window resizing
  if(vk_window->is_window_resized()){
    vk_swapchain->recreate_swapchain();
    return;
  }
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR){
    vk_swapchain->recreate_swapchain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}

}
