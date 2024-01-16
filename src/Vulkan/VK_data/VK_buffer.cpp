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
void VK_buffer::create_buffers(vk::structure::Object* vk_object){
  //---------------------------

  vk_object->has_xyz = false;
  vk_object->has_rgb = false;
  vk_object->has_uv = false;

  if(!vk_object->data->xyz.empty()){
    vk_memory->transfert_buffer_to_gpu(vk_object->data->xyz, &vk_object->xyz);
    vk_object->has_xyz = true;
  }
  if(!vk_object->data->rgb.empty()){
    vk_memory->transfert_buffer_to_gpu(vk_object->data->rgb, &vk_object->rgb);
    vk_object->has_rgb = true;
  }
  if(!vk_object->data->uv.empty()){
    vk_memory->transfert_buffer_to_gpu(vk_object->data->uv, &vk_object->uv);
    vk_object->has_uv = true;
  }

  //---------------------------
}
void VK_buffer::clean_buffers(vk::structure::Object* vk_object){
  //---------------------------

  this->clean_buffer(&vk_object->xyz);
  this->clean_buffer(&vk_object->rgb);
  this->clean_buffer(&vk_object->uv);

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
