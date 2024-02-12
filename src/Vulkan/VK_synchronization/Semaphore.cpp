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
void Semaphore::init_pool(){
  std::vector<vk::structure::Semaphore>& pool = struct_vulkan->pools.semaphore.pool;
  //---------------------------

  for(int i=0; i<struct_vulkan->pools.semaphore.size; i++){
    vk::structure::Semaphore vk_semaphore;

    this->create_semaphore(&vk_semaphore);
    vk_semaphore.is_available = true;

    pool.push_back(vk_semaphore);
  }

  //---------------------------
}
void Semaphore::clean_pool(){
  std::vector<vk::structure::Semaphore>& pool = struct_vulkan->pools.semaphore.pool;
  //---------------------------

  for(int i=0; i<struct_vulkan->pools.semaphore.size; i++){
    vk::structure::Semaphore* vk_semaphore = &pool[i];
    this->clean_semaphore(vk_semaphore);
  }

  //---------------------------
}
void Semaphore::reset(){
  std::vector<vk::structure::Semaphore>& pool = struct_vulkan->pools.semaphore.pool;
  //---------------------------

  for(int i=0; i<struct_vulkan->pools.semaphore.size; i++){
    vk::structure::Semaphore* vk_semaphore = &pool[i];
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

  result = vkCreateSemaphore(struct_vulkan->device.device, &info, nullptr, &semaphore->begin);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  result = vkCreateSemaphore(struct_vulkan->device.device, &info, nullptr, &semaphore->end);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphore");
  }

  //---------------------------
}
void Semaphore::clean_semaphore(vk::structure::Semaphore* semaphore){
  //---------------------------

  vkDestroySemaphore(struct_vulkan->device.device, semaphore->begin, nullptr);
  vkDestroySemaphore(struct_vulkan->device.device, semaphore->end, nullptr);

  //---------------------------
}

//Subfunction
vk::structure::Semaphore* Semaphore::query_free_semaphore(){
  std::vector<vk::structure::Semaphore>& pool = struct_vulkan->pools.semaphore.pool;
  //---------------------------

  //Find the first free command buffer
  for(int i=0; i<pool.size(); i++){
    vk::structure::Semaphore* vk_semaphore = &pool[i];

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





// OLD
//Semaphore function
void Semaphore::init_frame_semaphore(vk::structure::Frame* frame){
  //---------------------------

  //Create semaphore - Renderpass
  for(int i=0; i<4; i++){
    VkSemaphore semaphore;
    this->create_semaphore(semaphore);
  }


  //---------------------------
}
void Semaphore::clean_frame_semaphore(vk::structure::Frame* frame){
  //---------------------------


  //---------------------------
}

void Semaphore::create_semaphore(VkSemaphore& semaphore){
  //---------------------------

  VkSemaphoreCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkResult result = vkCreateSemaphore(struct_vulkan->device.device, &info, nullptr, &semaphore);
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
