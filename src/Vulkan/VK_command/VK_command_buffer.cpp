#include "VK_command_buffer.h"

#include <VK_struct/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_device/VK_physical_device.h>


//Constructor / Destructor
VK_command_buffer::VK_command_buffer(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_physical_device = new VK_physical_device(vk_engine);

  //---------------------------
}
VK_command_buffer::~VK_command_buffer(){}

//Command pool
void VK_command_buffer::create_command_pool(){
  //---------------------------

  int family_graphics = vk_physical_device->find_queue_family_graphics(struct_vulkan->device.physical_device);

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = family_graphics;

  //Command pool creation
  VkResult result = vkCreateCommandPool(struct_vulkan->device.device, &poolInfo, nullptr, &struct_vulkan->command_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_command_buffer::clean_command_pool(){
  //---------------------------

  vkDestroyCommandPool(struct_vulkan->device.device, struct_vulkan->command_pool, nullptr);

  //---------------------------
}

//Command buffer
void VK_command_buffer::allocate_command_buffer_primary(Struct_renderpass* renderpass){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = struct_vulkan->command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &allocInfo, &renderpass->command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void VK_command_buffer::allocate_command_buffer_secondary(Struct_data* data){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = struct_vulkan->command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
  allocInfo.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &allocInfo, &data->command_buffer_secondary);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
