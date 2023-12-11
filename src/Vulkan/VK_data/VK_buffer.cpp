#include "VK_buffer.h"

#include <VK_struct/Namespace.h>
#include <VK_command/VK_memory.h>


//Constructor / Destructor
VK_buffer::VK_buffer(vk::structure::Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_memory = new VK_memory(struct_vulkan);

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::create_buffers(vk::structure::Entity* data){
  //---------------------------

  vk_memory->transfert_buffer_to_gpu(&data->xyz, data->object->xyz);
  vk_memory->transfert_buffer_to_gpu(&data->rgb, data->object->rgb);
  vk_memory->transfert_buffer_to_gpu(&data->uv, data->object->uv);

  //---------------------------
}
void VK_buffer::clean_buffers(vk::structure::Entity* data){
  //---------------------------

  this->clean_buffer(&data->xyz);
  this->clean_buffer(&data->rgb);
  this->clean_buffer(&data->uv);

  //---------------------------
}
void VK_buffer::clean_buffer(vk::structure::Buffer* buffer){
  //---------------------------

  if(buffer->vbo != VK_NULL_HANDLE){
    vkDestroyBuffer(struct_vulkan->device.device, buffer->vbo, nullptr);
  }

  if(buffer->mem != VK_NULL_HANDLE){
    vkFreeMemory(struct_vulkan->device.device, buffer->mem, nullptr);
  }

  //---------------------------
}
