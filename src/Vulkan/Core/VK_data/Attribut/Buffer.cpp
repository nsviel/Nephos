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
void Buffer::create_buffer(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [type, vertex] : vk_object.map_vertex){
    vk_mem_allocator->allocate_empty_vertex_buffer(vertex.buffer, vertex.size_max);
    vk_mem_allocator->allocate_empty_stagger_buffer(vertex.stagger, vertex.size_max);
  }

  this->update_buffer(vk_object);

  //---------------------------
}
void Buffer::update_buffer(vk::structure::Object& vk_object){
  utl::base::Data& data = *vk_object.data;
  //---------------------------

  if(!data.xyz.empty()){
    vk::structure::Vertex vertex = vk_object.map_vertex[vk::vertex::XYZ];
    vertex.size = data.xyz.size();
    vk_mem_transfer->copy_vertex_to_gpu(vertex, data.xyz.data());
  }

  if(!data.rgba.empty()){
    vk::structure::Vertex vertex = vk_object.map_vertex[vk::vertex::RGBA];
    vertex.size = data.rgba.size();
    vk_mem_transfer->copy_vertex_to_gpu(vertex, data.rgba.data());
  }

  if(!data.uv.empty()){
    vk::structure::Vertex vertex = vk_object.map_vertex[vk::vertex::UV];
    vertex.size = data.uv.size();
    vk_mem_transfer->copy_vertex_to_gpu(vertex, data.uv.data());
  }

  //---------------------------
}
void Buffer::clean_buffers(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [type, vertex] : vk_object.map_vertex){
    this->clean_buffer(vertex.buffer);
    this->clean_buffer(vertex.stagger);
  }

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
