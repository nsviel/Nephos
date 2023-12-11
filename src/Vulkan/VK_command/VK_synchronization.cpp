#include "VK_synchronization.h"

#include <VK_struct/Namespace.h>
#include <VK_struct/Frame.h>


//Constructor / Destructor
VK_synchronization::VK_synchronization(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::init(){
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

  this->create_fence(struct_vulkan->synchro.fence);

  //---------------------------
}
void VK_synchronization::init_frame_sync(vk::structure::Frame* frame){
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

  this->create_fence(frame->fence);

  //---------------------------
}
void VK_synchronization::clean(){
  //---------------------------

  this->clean_semaphore(struct_vulkan->synchro.semaphore_image_ready);
  this->clean_semaphore(struct_vulkan->synchro.semaphore_render_done);
  this->clean_vec_semaphore(struct_vulkan->synchro.vec_semaphore_render);
  this->clean_fence(struct_vulkan->synchro.fence);

  //---------------------------
}
void VK_synchronization::clean_frame_sync(vk::structure::Frame* frame){
  //---------------------------

  this->clean_semaphore(frame->semaphore_image_ready);
  this->clean_semaphore(frame->semaphore_render_done);
  this->clean_vec_semaphore(frame->vec_semaphore_render);
  this->clean_fence(frame->fence);

  //---------------------------
}

//Synchronization object
void VK_synchronization::create_semaphore(VkSemaphore& semaphore){
  //---------------------------

  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkResult result = vkCreateSemaphore(struct_vulkan->device.device, &semaphoreInfo, nullptr, &semaphore);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  //---------------------------
}
void VK_synchronization::create_fence(VkFence& fence){
  //---------------------------

  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  VkResult result = vkCreateFence(struct_vulkan->device.device, &fenceInfo, nullptr, &fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create fence");
  }

  vkResetFences(struct_vulkan->device.device, 1, &fence);

  //---------------------------
}

//Deletetion function
void VK_synchronization::clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore){
  //---------------------------

  for(int i=0; i<vec_semaphore.size(); i++){
    VkSemaphore& semaphore = vec_semaphore[i];
    this->clean_semaphore(semaphore);
  }
  vec_semaphore.clear();

  //---------------------------
}
void VK_synchronization::clean_semaphore(VkSemaphore& semaphore){
  //---------------------------

  vkDestroySemaphore(struct_vulkan->device.device, semaphore, nullptr);

  //---------------------------
}
void VK_synchronization::clean_vec_fence(vector<VkFence>& vec_fence){
  //---------------------------

  for(int i=0; i<vec_fence.size(); i++){
    VkFence& fence = vec_fence[i];
    this->clean_fence(fence);
  }
  vec_fence.clear();

  //---------------------------
}
void VK_synchronization::clean_fence(VkFence& fence){
  //---------------------------

  vkDestroyFence(struct_vulkan->device.device, fence, nullptr);

  //---------------------------
}
