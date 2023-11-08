#include "VK_synchronization.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_struct/Struct_synchro.h>
#include <VK_device/VK_device.h>


//Constructor / Destructor
VK_synchronization::VK_synchronization(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->struct_synchro = vk_engine->get_struct_synchro();
  this->vk_engine = vk_engine;
  this->vk_device = new VK_device(vk_engine);

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::init_frame_sync(Struct_frame* frame){
  //---------------------------

  //Create semaphore - Renderpass
  for(int i=0; i<4; i++){
    VkSemaphore semaphore;
    this->create_semaphore(semaphore);
    struct_synchro->vec_semaphore_render.push_back(semaphore);
  }

  //Create semaphore - Image acquisition
  VkSemaphore semaphore_image;
  this->create_semaphore(semaphore_image);
  struct_synchro->vec_semaphore_render.push_back(semaphore_image);

  //Create fence
  VkFence fence;
  this->create_fence(fence);
  struct_synchro->vec_fence.push_back(fence);

  //---------------------------
}
void VK_synchronization::clean_frame_sync(Struct_frame* frame){
  //---------------------------

  this->clean_vec_semaphore(struct_synchro->vec_semaphore_render);
  this->clean_vec_semaphore(struct_synchro->vec_semaphore_image);
  this->clean_vec_fence(struct_synchro->vec_fence);

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

  //---------------------------
}

//Deletetion function
void VK_synchronization::clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore){
  //---------------------------

  for(int i=0; i<vec_semaphore.size(); i++){
    VkSemaphore& semaphore = vec_semaphore[i];
    vkDestroySemaphore(struct_vulkan->device.device, semaphore, nullptr);
  }
  vec_semaphore.clear();

  //---------------------------
}
void VK_synchronization::clean_vec_fence(vector<VkFence>& vec_fence){
  //---------------------------

  for(int i=0; i<vec_fence.size(); i++){
    VkFence& fence = vec_fence[i];
    vkDestroyFence(struct_vulkan->device.device, fence, nullptr);
  }
  vec_fence.clear();

  //---------------------------
}
