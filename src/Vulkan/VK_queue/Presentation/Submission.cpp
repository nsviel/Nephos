#include "Submission.h"

#include <Vulkan/Namespace.h>


namespace vk::queue::presentation{

//Constructor / Destructor
Submission::Submission(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_drawer = new vk::draw::Graphical(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);

  //---------------------------
}
Submission::~Submission(){}

//Main function
void Submission::process_command(){
  //---------------------------

  //Init
  std::vector<vk::structure::Command*> vec_command;
  vk::synchro::structure::Semaphore semaphore = *vk_semaphore->query_free_semaphore();

  //Acquiere image
  bool sucess = vk_swapchain->acquire_next_image(&semaphore);
  if(!sucess) return;

  //Rendering
  vk_drawer->record_renderpass(vec_command, semaphore);
  vk_drawer->copy_to_swapchain(vec_command, semaphore);

  //Submission
  this->submit_rendering(vec_command, &semaphore);
  this->submit_presentation(&semaphore);
  this->next_frame_ID();
  vk_semaphore->reset_pool();
  
  //---------------------------
}

//Subfunction
void Submission::submit_rendering(std::vector<vk::structure::Command*>& vec_command, vk::synchro::structure::Semaphore* semaphore){
  //---------------------------

  vk::command::structure::Set* set = new vk::command::structure::Set();
  set->vec_command = vec_command;
  set->semaphore = semaphore->handle;
  set->supress = false;
  vk_struct->queue.graphics->add_command(set);
  set->wait_until_done();
  delete set;

  //---------------------------
}
void Submission::submit_presentation(vk::synchro::structure::Semaphore* semaphore){
  vk::structure::Swapchain* swapchain = &vk_struct->swapchain;
  //---------------------------

  VkPresentInfoKHR presentation_info{};
  presentation_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentation_info.waitSemaphoreCount = 1;
  presentation_info.pWaitSemaphores = &semaphore->handle;
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
void Submission::next_frame_ID(){
  vk::structure::Swapchain* swapchain = &vk_struct->swapchain;
  //---------------------------

  int current_ID = swapchain->current_ID;
  current_ID = (current_ID + 1) % vk_struct->instance.max_frame_inflight;
  swapchain->current_ID = current_ID;

  //---------------------------
}

}
