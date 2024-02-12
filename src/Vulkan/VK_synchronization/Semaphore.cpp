#include "Semaphore.h"

#include <Vulkan/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Semaphore::Semaphore(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Semaphore::~Semaphore(){}

//Main function
void Semaphore::init(){
  //---------------------------

  //Create semaphore - Renderpass
  for(int i=0; i<4; i++){
    VkSemaphore semaphore;
    this->create_semaphore(semaphore);
    struct_vulkan->synchro.vec_semaphore_render.push_back(semaphore);
  }

  //Create semaphore - Image ready
  VkSemaphore semaphore_image_ready;
  this->create_semaphore(semaphore_image_ready);
  struct_vulkan->synchro.semaphore_image_ready = semaphore_image_ready;

  //Create semaphore - Image ready
  VkSemaphore semaphore_render_done;
  this->create_semaphore(semaphore_render_done);
  struct_vulkan->synchro.semaphore_render_done = semaphore_render_done;

  //---------------------------
}
void Semaphore::clean(){
  //---------------------------
/*
  this->clean_semaphore(struct_vulkan->synchro.semaphore_image_ready);
  this->clean_semaphore(struct_vulkan->synchro.semaphore_render_done);
  this->clean_vec_semaphore(struct_vulkan->synchro.vec_semaphore_render);
*/
  //---------------------------
}

//Semaphore function
void Semaphore::init_frame_semaphore(vk::structure::Frame* frame){
  //---------------------------

  //Create semaphore - Renderpass
  for(int i=0; i<4; i++){
    VkSemaphore semaphore;
    this->create_semaphore(semaphore);
    frame->vec_semaphore_render.push_back(semaphore);
  }

  //Create semaphore - Image ready
  VkSemaphore semaphore_image_ready;
  this->create_semaphore(semaphore_image_ready);
  frame->semaphore_image_ready = semaphore_image_ready;

  //Create semaphore - Image ready
  VkSemaphore semaphore_render_done;
  this->create_semaphore(semaphore_render_done);
  frame->semaphore_render_done = semaphore_render_done;

  //---------------------------
}
void Semaphore::clean_frame_semaphore(vk::structure::Frame* frame){
  //---------------------------

  this->clean_semaphore(frame->semaphore_image_ready);
  this->clean_semaphore(frame->semaphore_render_done);
  this->clean_vec_semaphore(frame->vec_semaphore_render);

  //---------------------------
}

void Semaphore::create_semaphore(VkSemaphore& semaphore){
  //---------------------------

  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkResult result = vkCreateSemaphore(struct_vulkan->device.device, &semaphoreInfo, nullptr, &semaphore);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  //---------------------------
}
void Semaphore::clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore){
  //---------------------------

  for(int i=0; i<vec_semaphore.size(); i++){
    VkSemaphore& semaphore = vec_semaphore[i];
    this->clean_semaphore(semaphore);
  }
  vec_semaphore.clear();

  //---------------------------
}
void Semaphore::clean_semaphore(VkSemaphore& semaphore){
  //---------------------------

  vkDestroySemaphore(struct_vulkan->device.device, semaphore, nullptr);

  //---------------------------
}

//Subfunction

}
