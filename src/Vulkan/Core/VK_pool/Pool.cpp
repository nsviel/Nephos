#include "Pool.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
Pool::Pool(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Pool::~Pool(){}

//Main function
void Pool::init(){
  //---------------------------

  this->create_descriptor_set_pool();

  //---------------------------
}
void Pool::clean(){
  //---------------------------

  this->clean_descriptor_set_pool();

  //---------------------------
}

//Descriptor pool
void Pool::create_descriptor_set_pool(){
  //---------------------------

  //Maximum number of descriptor per type
  VkDescriptorPoolSize pool_size[] ={
    { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
    { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
    { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
    { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
  };

  VkDescriptorPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
  pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_size);
  pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_size);
  pool_info.pPoolSizes = pool_size;
  VkResult result = vkCreateDescriptorPool(vk_struct->core.device.handle, &pool_info, nullptr, &vk_struct->core.pools.descriptor_set.pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gui");
  }

  //---------------------------
}
void Pool::reset_descriptor_set_pool(){
  //---------------------------

  VkResult result = vkResetDescriptorPool(vk_struct->core.device.handle, vk_struct->core.pools.descriptor_set.pool, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to reset descripto pool");
  }

  //---------------------------
}
void Pool::clean_descriptor_set_pool(){
  //---------------------------

  vkDestroyDescriptorPool(vk_struct->core.device.handle, vk_struct->core.pools.descriptor_set.pool, nullptr);

  //---------------------------
}

//Command pool
void Pool::create_command_pool(vk::pool::structure::Command_buffer* pool, int family_ID){
  //---------------------------

  //Command pool info
  VkCommandPoolCreateInfo pool_info{};
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  pool_info.queueFamilyIndex = family_ID;

  //Command pool creation
  VkResult result = vkCreateCommandPool(vk_struct->core.device.handle, &pool_info, nullptr, &pool->allocator);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void Pool::reset_command_pool(vk::pool::structure::Command_buffer* pool){
  //---------------------------

  VkResult result = vkResetCommandPool(vk_struct->core.device.handle, pool->allocator, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to reset command pool");
  }

  //---------------------------
}
void Pool::clean_command_pool(vk::pool::structure::Command_buffer* pool){
  //---------------------------

  vkDestroyCommandPool(vk_struct->core.device.handle, pool->allocator, nullptr);

  //---------------------------
}

}
