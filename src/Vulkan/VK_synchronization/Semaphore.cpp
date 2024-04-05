#include "Semaphore.h"

#include <Vulkan/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Semaphore::Semaphore(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Semaphore::~Semaphore(){}

//Pool function
void Semaphore::init_pool(){
  vk::pool::Semaphore* pool = &vk_struct->pools.semaphore;
  //---------------------------

  //Number of semaphore
  int number = vk_struct->device.physical_device.discrete_gpu ? 100 : 10;
  pool->size = number;

  //Create a pool of semaphore number
  for(int i=0; i<number; i++){
    vk::structure::Semaphore vk_semaphore;

    this->create_semaphore(&vk_semaphore);
    vk_semaphore.is_available = true;

    pool->tank.push_back(vk_semaphore);
  }

  //---------------------------
}
void Semaphore::clean_pool(){
  vk::pool::Semaphore* pool = &vk_struct->pools.semaphore;
  //---------------------------

  for(int i=0; i<pool->size; i++){
    vk::structure::Semaphore* vk_semaphore = &pool->tank[i];
    this->clean_semaphore(vk_semaphore);
  }

  //---------------------------
}
void Semaphore::reset_pool(){
  vk::pool::Semaphore* pool = &vk_struct->pools.semaphore;
  //---------------------------

  for(int i=0; i<pool->size; i++){
    vk::structure::Semaphore* vk_semaphore = &pool->tank[i];
    vk_semaphore->is_available = true;
  }

  //---------------------------
}

//Semaphore function
void Semaphore::create_semaphore(vk::structure::Semaphore* semaphore){
  VkResult result;
  //---------------------------

  VkSemaphoreCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  result = vkCreateSemaphore(vk_struct->device.handle, &info, nullptr, &semaphore->begin);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  result = vkCreateSemaphore(vk_struct->device.handle, &info, nullptr, &semaphore->end);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  //---------------------------
}
void Semaphore::clean_semaphore(vk::structure::Semaphore* semaphore){
  //---------------------------

  vkDestroySemaphore(vk_struct->device.handle, semaphore->begin, nullptr);
  vkDestroySemaphore(vk_struct->device.handle, semaphore->end, nullptr);

  //---------------------------
}

//Subfunction
vk::structure::Semaphore* Semaphore::query_free_semaphore(){
  vk::pool::Semaphore* pool = &vk_struct->pools.semaphore;
  //---------------------------

  //Find the first free command buffer
  for(int i=0; i<pool->tank.size(); i++){
    vk::structure::Semaphore* vk_semaphore = &pool->tank[i];

    if(vk_semaphore->is_available){
      vk_semaphore->is_available = false;
      return vk_semaphore;
    }
  }

  //Error message
  cout<<"[error] not enough semaphore"<<endl;

  //---------------------------
  return nullptr;
}

}
