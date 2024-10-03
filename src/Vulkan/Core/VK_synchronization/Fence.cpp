#include "Fence.h"

#include <Vulkan/Namespace.h>
#include <random>


namespace vk::synchro{

//Constructor / Destructor
Fence::Fence(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Fence::~Fence(){}

//Main function
void Fence::init_pool(){
  vk::pool::structure::Fence& pool = vk_struct->core.pools.fence;
  //---------------------------

  //Number of fence
  pool.size = vk_struct->core.device.physical_device.discrete_gpu ? 100 : 10;

  //Create a pool of fence number
  for(int i=0; i<pool.size; i++){
    auto fence = std::make_shared<vk::structure::Fence>();

    this->create_fence(*fence);
    this->reset_fence(*fence);

    pool.tank.push_back(fence);
  }

  //---------------------------
}
void Fence::clean_pool(){
  vk::pool::structure::Fence& pool = vk_struct->core.pools.fence;
  //---------------------------

  for(auto& fence : pool.tank){
    this->clean_fence(*fence);
  }

  //---------------------------
}

//Subfunction
void Fence::create_fence(vk::structure::Fence& fence){
  //---------------------------

  VkFenceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  VkResult result = vkCreateFence(vk_struct->core.device.handle, &info, nullptr, &fence.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create fence");
  }

  //---------------------------
}
void Fence::clean_fence(vk::structure::Fence& fence){
  //---------------------------

  vkDestroyFence(vk_struct->core.device.handle, fence.handle, nullptr);

  //---------------------------
}
void Fence::reset_fence(vk::structure::Fence& fence){
  //---------------------------

  VkResult result = vkResetFences(vk_struct->core.device.handle, 1, &fence.handle);
  if(result != VK_SUCCESS){
    std::cout<<"[error] reseting fence"<<std::endl;
  }

  fence.is_available = true;

  //---------------------------
}
bool Fence::is_fence_available(vk::structure::Fence& fence){
  //---------------------------

  VkResult result = vkGetFenceStatus(vk_struct->core.device.handle, fence.handle);

  bool is_available = false;
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
std::shared_ptr<vk::structure::Fence> Fence::query_free_fence(){
  vk::pool::structure::Fence& pool = vk_struct->core.pools.fence;
  //---------------------------

  std::lock_guard<std::mutex> lock(pool.mutex);

  // Random number generator setup
  std::random_device rd;  // Seed for the random number generator
  std::mt19937 gen(rd()); // Mersenne Twister PRNG
  std::uniform_int_distribution<int> distr(0, pool.tank.size() - 1);

  //Find the first free command buffer
  int index;
  do{
    index = distr(gen); // Generate a random index
    auto fence = pool.tank[index];

    if(fence->is_available){
      fence->is_available = false;
      return fence;
    }
  }while(true);

  //Error message
  std::cout<<"[error] not enough fence"<<std::endl;

  //---------------------------
  return nullptr;
}

}
