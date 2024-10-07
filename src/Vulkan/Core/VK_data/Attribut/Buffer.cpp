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
void Buffer::create_buffer(vk::structure::Vertex& vertex){
  //---------------------------

  vk_mem_allocator->allocate_empty_vertex_buffer(vertex.buffer, vertex.size_max);
  vk_mem_allocator->allocate_empty_stagger_buffer(vertex.stagger, vertex.size_max);

  //---------------------------
}
void Buffer::update_buffer(vk::structure::Vertex& vertex, void* data){
  //---------------------------

  vk_mem_transfer->copy_vertex_to_gpu(vertex, data);

  //---------------------------
}
void Buffer::clean_buffer(vk::structure::Buffer& buffer){
  //---------------------------

  if(buffer.vbo != VK_NULL_HANDLE){
    vkDestroyBuffer(vk_struct->core.device.handle, buffer.vbo, nullptr);
  }

  if(buffer.mem != VK_NULL_HANDLE){
    vkFreeMemory(vk_struct->core.device.handle, buffer.mem, nullptr);
  }

  //---------------------------
}

//Subfunction


}
