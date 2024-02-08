#include "Fence.h"

#include <Vulkan/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Fence::Fence(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Fence::~Fence(){}

//Main function
void Fence::init(){
  std::vector<vk::structure::Fence>& pool = struct_vulkan->pools.fence.pool;
  //---------------------------

  for(int i=0; i<struct_vulkan->pools.fence.size; i++){
    vk::structure::Fence vk_fence;

    this->create_fence(vk_fence.fence);
    pool.push_back(vk_fence);
  }

  this->create_fence(struct_vulkan->synchro.fence);

  //---------------------------
}

//Fence function
void Fence::create_fence(VkFence& fence){
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
void Fence::clean_fence(VkFence& fence){
  //---------------------------

  vkDestroyFence(struct_vulkan->device.device, fence, nullptr);

  //---------------------------
}
void Fence::reset_fence(VkFence& fence){
  //---------------------------

  VkResult result = vkResetFences(struct_vulkan->device.device, 1, &fence);
  if (result != VK_SUCCESS) {
    cout<<"[error] reseting fence"<<endl;
  }

  //---------------------------
}

//Subfunction
vk::structure::Fence* Fence::query_free_fence(){
  std::vector<vk::structure::Fence>& pool = struct_vulkan->pools.fence.pool;
  //---------------------------

  //Find the first free command buffer
  for(int i=0; i<pool.size(); i++){
    vk::structure::Fence* fence = &pool[i];

    if(fence->is_available){
      fence->is_available = false;
      return fence;
    }
  }

  //Error message
  cout<<"[error] not enough fence"<<endl;

  //---------------------------
  return nullptr;
}
bool Fence::is_fence_available(VkFence& fence){
  bool is_available = false;
  //---------------------------

  VkResult result = vkGetFenceStatus(struct_vulkan->device.device, fence);

  //Operation completed
  if(result == VK_SUCCESS){
    is_available = true;
  }
  //Operation is running
  else if(result == VK_NOT_READY){
    is_available = false;
  }
  //Error in fence status check
  else{

  }

  //---------------------------
  return is_available;
}

}
