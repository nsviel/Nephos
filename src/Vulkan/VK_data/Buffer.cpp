#include "Buffer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Buffer::Buffer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);

  //---------------------------
}
Buffer::~Buffer(){}

//Main function
void Buffer::create_buffer(vk::structure::Object* vk_object){
  VkDeviceSize size;
  //---------------------------

  int max_data = get_size_buffer(vk_object);
  if(max_data == 0){
    //cout<<"[error] max buffer size equal 0"<<std::endl;
    return;
  }

  //Find buffer size
  size = sizeof(glm::vec3) * max_data;
  vk_mem_allocator->allocate_empty_vertex_buffer(&vk_object->buffer.xyz, size);
  vk_mem_allocator->allocate_empty_stagger_buffer(&vk_object->buffer.xyz_stagger, size);

  size = sizeof(glm::vec4) * max_data;
  vk_mem_allocator->allocate_empty_vertex_buffer(&vk_object->buffer.rgba, size);
  vk_mem_allocator->allocate_empty_stagger_buffer(&vk_object->buffer.rgba_stagger, size);

  size  = sizeof(glm::vec2) * max_data;
  vk_mem_allocator->allocate_empty_vertex_buffer(&vk_object->buffer.uv, size);
  vk_mem_allocator->allocate_empty_stagger_buffer(&vk_object->buffer.uv_stagger, size);

  this->update_buffer(vk_object);

  //---------------------------
}
void Buffer::update_buffer(vk::structure::Object* vk_object){
  utl::base::Data& data = *vk_object->data;
  //---------------------------

  if(data.xyz.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec3) * data.xyz.size();
    vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.xyz, &vk_object->buffer.xyz_stagger, data.xyz.data(), data_size);
  }

  if(data.rgba.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec4) * data.rgba.size();
    vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.rgba, &vk_object->buffer.rgba_stagger, data.rgba.data(), data_size);
  }

  if(data.uv.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec2) * data.uv.size();
    vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.uv, &vk_object->buffer.uv_stagger, data.uv.data(), data_size);
  }

  //---------------------------
}
void Buffer::clean_buffers(vk::structure::Object* vk_object){
  //---------------------------

  this->clean_buffer(&vk_object->buffer.xyz);
  this->clean_buffer(&vk_object->buffer.rgba);
  this->clean_buffer(&vk_object->buffer.uv);

  this->clean_buffer(&vk_object->buffer.xyz_stagger);
  this->clean_buffer(&vk_object->buffer.rgba_stagger);
  this->clean_buffer(&vk_object->buffer.uv_stagger);

  //---------------------------
}
void Buffer::clean_buffer(vk::data::structure::Buffer* buffer){
  //---------------------------

  if(buffer->vbo != VK_NULL_HANDLE){
    vkDestroyBuffer(vk_struct->device.handle, buffer->vbo, nullptr);
  }

  if(buffer->mem != VK_NULL_HANDLE){
    vkFreeMemory(vk_struct->device.handle, buffer->mem, nullptr);
  }

  //---------------------------
}

//Subfunction
int Buffer::get_size_buffer(vk::structure::Object* vk_object){
  utl::base::Data& data = *vk_object->data;
  //---------------------------

  int max_data = (data.nb_data_max != -1) ? data.nb_data_max : data.xyz.size();

  //---------------------------
  return max_data;
}


}
