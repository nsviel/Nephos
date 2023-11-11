#include "VK_command_buffer.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_device/VK_physical_device.h>


//Constructor / Destructor
VK_command_buffer::VK_command_buffer(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_physical_device = new VK_physical_device(struct_vulkan);

  //---------------------------
}
VK_command_buffer::~VK_command_buffer(){}

//Command buffer
void VK_command_buffer::allocate_command_buffer_primary(VkCommandBuffer& command_buffer){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool = struct_vulkan->pool.command;
  alloc_info.commandBufferCount = 1;
  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void VK_command_buffer::allocate_command_buffer_secondary(Struct_data* data){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
  alloc_info.commandPool = struct_vulkan->pool.command;
  alloc_info.commandBufferCount = 1;

  VkResult result = vkAllocateCommandBuffers(struct_vulkan->device.device, &alloc_info, &data->command_buffer_secondary);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
