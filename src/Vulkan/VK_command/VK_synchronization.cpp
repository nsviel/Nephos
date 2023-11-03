#include "VK_synchronization.h"
#include "../VK_engine.h"
#include "../VK_struct/struct_vulkan.h"
#include "../VK_device/VK_device.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_device = vk_engine->get_vk_device();

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

  //---------------------------
}
void VK_synchronization::clean_frame_sync(Frame* frame){
  //---------------------------

  this->clean_semaphore(frame->semaphore_image_ready);
  this->clean_semaphore(frame->semaphore_scene_ready);
  this->clean_semaphore(frame->semaphore_edl_ready);
  this->clean_semaphore(frame->semaphore_ui_ready);
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
