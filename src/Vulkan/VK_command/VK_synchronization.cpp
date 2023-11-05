#include "VK_synchronization.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_struct/struct_synchro.h>
#include <VK_device/VK_device.h>


//Constructor / Destructor
VK_synchronization::VK_synchronization(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_device = vk_engine->get_vk_device();
  this->struct_synchro = vk_engine->get_struct_synchro();

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::init_frame_sync(Frame* frame){
  //---------------------------

  this->create_semaphore(frame->semaphore_image_ready);
  this->create_semaphore(frame->semaphore_edl_ready);
  this->create_semaphore(frame->semaphore_scene_ready);
  this->create_semaphore(frame->semaphore_ui_ready);
  this->create_fence(frame->fence);

  //Create semaphore - Renderpass
  for(int i=0; i<4; i++){
    VkSemaphore semaphore;
    this->create_semaphore(semaphore);
    struct_synchro->vec_semaphore_render.push_back(semaphore);
  }

  //Create semaphore - Presentation
  VkSemaphore semaphore_present;
  this->create_semaphore(semaphore_present);
  struct_synchro->vec_semaphore_presen.push_back(semaphore_present);

  //Create semaphore - Image acquisition
  VkSemaphore semaphore_image;
  this->create_semaphore(semaphore_image);
  struct_synchro->vec_semaphore_image.push_back(semaphore_image);

  //Create fence
  VkFence fence;
  this->create_fence(fence);
  struct_synchro->vec_fence.push_back(fence);

  //---------------------------
}
void VK_synchronization::clean_frame_sync(Frame* frame){
  //---------------------------

  this->clean_semaphore(frame->semaphore_image_ready);
  this->clean_semaphore(frame->semaphore_scene_ready);
  this->clean_semaphore(frame->semaphore_edl_ready);
  this->clean_semaphore(frame->semaphore_ui_ready);
  this->clean_fence(frame->fence);

  //Clean semaphore
  this->clean_vec_semaphore(struct_synchro->vec_semaphore_render);
  this->clean_vec_semaphore(struct_synchro->vec_semaphore_image);
  this->clean_vec_semaphore(struct_synchro->vec_semaphore_presen);

  //Clean fence
  for(int i=0; i<struct_synchro->vec_fence.size(); i++){
    VkFence& fence = struct_synchro->vec_fence[i];
    this->clean_fence(fence);
  }
  struct_synchro->vec_fence.clear();

  //---------------------------
}

//Synchronization object
void VK_synchronization::create_semaphore(VkSemaphore& semaphore){
  //---------------------------

  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkResult result = vkCreateSemaphore(struct_vulkan->device.device, &semaphoreInfo, nullptr, &semaphore);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphores!");
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
    throw std::runtime_error("[error] failed to create fence!");
  }

  //---------------------------
}

//Deletetion function
void VK_synchronization::clean_semaphore(VkSemaphore& semaphore){
  //---------------------------

  vkDestroySemaphore(struct_vulkan->device.device, semaphore, nullptr);

  //---------------------------
}
void VK_synchronization::clean_fence(VkFence& fence){
  //---------------------------

  vkDestroyFence(struct_vulkan->device.device, fence, nullptr);

  //---------------------------
}
void VK_synchronization::clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore){
  //---------------------------

  for(int i=0; i<vec_semaphore.size(); i++){
    VkSemaphore& semaphore = vec_semaphore[i];
    this->clean_semaphore(semaphore);
  }
  vec_semaphore.clear();

  //---------------------------
}
