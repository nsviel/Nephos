#include "Fence.h"

#include <Vulkan/Namespace.h>
#include <random>


namespace vk::synchro{

//Constructor / Destructor
Fence::Fence(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Fence::~Fence(){}

//Pool function
void Fence::init_pool(){
  vk::pool::Fence* pool = &vk_struct->pools.fence;
  //---------------------------

  //Number of fence
  int number = vk_struct->device.physical_device.discrete_gpu ? 100 : 10;
  pool->size = number;

  //Create a pool of fence number
  for(int i=0; i<number; i++){
    vk::structure::Fence vk_fence;

    this->create_fence(&vk_fence);
    this->reset_fence(&vk_fence);

    pool->tank.push_back(vk_fence);
  }

  //---------------------------
}
void Fence::clean_pool(){
  std::vector<vk::structure::Fence>& pool = vk_struct->pools.fence.tank;
  //---------------------------

  for(int i=0; i<vk_struct->pools.fence.size; i++){
    vk::structure::Fence* vk_fence = &pool[i];

    this->clean_fence(vk_fence);
  }

  //---------------------------
}

//Fence function
void Fence::create_fence(vk::structure::Fence* fence){
  //---------------------------

  VkFenceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  VkResult result = vkCreateFence(vk_struct->device.handle, &info, nullptr, &fence->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create fence");
  }

  //---------------------------
}
void Fence::clean_fence(vk::structure::Fence* fence){
  //---------------------------

  vkDestroyFence(vk_struct->device.handle, fence->fence, nullptr);

  //---------------------------
}
void Fence::reset_fence(vk::structure::Fence* fence){
  if(fence == nullptr) return;
  //---------------------------

  VkResult result = vkResetFences(vk_struct->device.handle, 1, &fence->fence);
  if(result != VK_SUCCESS){
    cout<<"[error] reseting fence"<<endl;
  }

  fence->is_available = true;

  //---------------------------
}

//Subfunction
vk::structure::Fence* Fence::query_free_fence(){
  vk::pool::Fence* pool = &vk_struct->pools.fence;
  //---------------------------

  // Random number generator setup
  std::random_device rd;  // Seed for the random number generator
  std::mt19937 gen(rd()); // Mersenne Twister PRNG
  std::uniform_int_distribution<int> distr(0, pool->tank.size() - 1);

  // Mutex for synchronization
  static std::mutex mtx;

  //Find the first free command buffer
  int index;
  vk::structure::Fence* fence;
  do{
    index = distr(gen); // Generate a random index
    fence = &pool->tank[index];

    // Lock the mutex before accessing and modifying the flag
    std::lock_guard<std::mutex> lock(mtx);
    if(fence->is_available){
      fence->is_available = false;
      return fence;
    }
  }while(true);

  //Error message
  cout<<"[error] not enough fence"<<endl;

  //---------------------------
  return nullptr;
}
bool Fence::is_fence_available(vk::structure::Fence* fence){
  bool is_available = false;
  //---------------------------

  if(fence == nullptr) return true;

  VkResult result = vkGetFenceStatus(vk_struct->device.handle, fence->fence);

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
