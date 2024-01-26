#include "VK_pool.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
VK_pool::VK_pool(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_pool::~VK_pool(){}

//Main function
void VK_pool::init(){
  //---------------------------

  this->create_descriptor_pool();
  this->create_command_pool();

  //---------------------------
}
void VK_pool::clean(){
  //---------------------------

  this->clean_descriptor_pool();
  this->clean_command_pool();

  //---------------------------
}

//Descriptor pool
void VK_pool::create_descriptor_pool(){
  //---------------------------

  int pool_nb_uniform = 1000;
  int pool_nb_sampler = 1000;
  int pool_nb_descriptor = 1000;

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
  VkResult result = vkCreateDescriptorPool(struct_vulkan->device.device, &pool_info, nullptr, &struct_vulkan->pool.descriptor);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create gui");
  }

  //---------------------------
}
void VK_pool::reset_descriptor_pool(){
  //---------------------------

  VkResult result = vkResetDescriptorPool(struct_vulkan->device.device, struct_vulkan->pool.descriptor, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to reset descripto pool");
  }

  //---------------------------
}
void VK_pool::clean_descriptor_pool(){
  //---------------------------

  vkDestroyDescriptorPool(struct_vulkan->device.device, struct_vulkan->pool.descriptor, nullptr);

  //---------------------------
}

//Command pool
void VK_pool::create_command_pool(){
  //---------------------------

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = struct_vulkan->device.physical_device.queue_graphics_idx;

  //Command pool creation
  VkResult result = vkCreateCommandPool(struct_vulkan->device.device, &poolInfo, nullptr, &struct_vulkan->pool.command);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_pool::reset_command_pool(){
  //---------------------------

  VkResult result = vkResetCommandPool(struct_vulkan->device.device, struct_vulkan->pool.command, 0);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to reset command pool");
  }

  //---------------------------
}
void VK_pool::clean_command_pool(){
  //---------------------------

  vkDestroyCommandPool(struct_vulkan->device.device, struct_vulkan->pool.command, nullptr);

  //---------------------------
}

}
