#include "Semaphore.h"

#include <Vulkan/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Semaphore::Semaphore(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Semaphore::~Semaphore(){}

//Main function
void Semaphore::init_pool(){
  vk::pool::structure::Semaphore* pool = &vk_struct->core.pools.semaphore;
  //---------------------------

  //Number of semaphore
  int number = vk_struct->core.device.physical_device.discrete_gpu ? 100 : 10;
  pool->size = number;

  //Create a pool of semaphore number
  for(int i=0; i<number; i++){
    std::shared_ptr<vk::structure::Semaphore> semaphore = std::make_shared<vk::structure::Semaphore>();

    this->create_semaphore(*semaphore);
    semaphore->is_available = true;

    pool->tank.push_back(semaphore);
  }

  //---------------------------
}
void Semaphore::clean_pool(){
  vk::pool::structure::Semaphore* pool = &vk_struct->core.pools.semaphore;
  //---------------------------

  for(auto& semaphore : pool->tank){
    this->clean_semaphore(*semaphore);
  }

  //---------------------------
}
void Semaphore::reset_pool(){
  vk::pool::structure::Semaphore* pool = &vk_struct->core.pools.semaphore;
  //---------------------------

  for(auto& semaphore : pool->tank){
    this->reset_semaphore(*semaphore);
  }

  //---------------------------
}

//Subfunction
void Semaphore::create_semaphore(vk::structure::Semaphore& semaphore){
  VkResult result;
  //---------------------------

  VkSemaphoreCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  result = vkCreateSemaphore(vk_struct->core.device.handle, &info, nullptr, &semaphore.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  //---------------------------
}
void Semaphore::clean_semaphore(vk::structure::Semaphore& semaphore){
  //---------------------------

  vkDestroySemaphore(vk_struct->core.device.handle, semaphore.handle, nullptr);

  //---------------------------
}
void Semaphore::reset_semaphore(vk::structure::Semaphore& semaphore){
  //---------------------------
/*
  // Initialize semaphore signal info
  VkSemaphoreSignalInfo signalInfo{};
  signalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
  signalInfo.semaphore = semaphore.handle; // Assuming 'handle' is the Vulkan semaphore handle
  signalInfo.value = 0;

  // Call vkSignalSemaphoreKHR to signal (reset) the semaphore
  VkResult result = vkSignalSemaphore(vk_struct->core.device.handle, &signalInfo);
  if(result != VK_SUCCESS){
      throw std::runtime_error("Failed to reset semaphore!");
  }
*/
  // Update the semaphore state if needed
  semaphore.is_available = true;

  //---------------------------
}
std::shared_ptr<vk::structure::Semaphore> Semaphore::query_free_semaphore(){
  vk::pool::structure::Semaphore* pool = &vk_struct->core.pools.semaphore;
  //---------------------------

  std::lock_guard<std::mutex> lock(pool->mutex);

  //Find the first free command buffer
  for(auto& semaphore : pool->tank){
    if(semaphore->is_available){
      semaphore->is_available = false;
      return semaphore;
    }
  }

  //Error message
  std::cout<<"[error] not enough semaphore"<<std::endl;

  //---------------------------
  return nullptr;
}

}
