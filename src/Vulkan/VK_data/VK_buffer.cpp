#include "VK_buffer.h"

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_command/VK_memory.h>


//Constructor / Destructor
VK_buffer::VK_buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_memory = new VK_memory(struct_vulkan);

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::create_buffers(vk::structure::Object* data){
  //---------------------------

  data->has_xyz = false;
  data->has_rgb = false;
  data->has_uv = false;

  if(!data->object->xyz.empty()){
    vk_memory->transfert_buffer_to_gpu(data->object->xyz, &data->xyz);
    data->has_xyz = true;
  }
  if(!data->object->rgb.empty()){
    vk_memory->transfert_buffer_to_gpu(data->object->rgb, &data->rgb);
    data->has_rgb = true;
  }
  if(!data->object->uv.empty()){
    vk_memory->transfert_buffer_to_gpu(data->object->uv, &data->uv);
    data->has_uv = true;
  }

  //---------------------------
}
void VK_buffer::clean_buffers(vk::structure::Object* data){
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
