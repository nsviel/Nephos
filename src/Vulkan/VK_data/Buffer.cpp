#include "Buffer.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Buffer::Buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_mem_allocator = new vk::memory::Allocator(struct_vulkan);
  this->vk_mem_transfer = new vk::memory::Transfer(struct_vulkan);

  //---------------------------
}
Buffer::~Buffer(){}

//Main function
void Buffer::create_buffers(vk::structure::Object* vk_object){
  VkDeviceSize size;
  //---------------------------

  int max_data = get_size_buffer(vk_object);
  if(max_data == 0) return;

  //Find buffer size
  size = sizeof(glm::vec3) * max_data;
  vk_mem_allocator->allocate_empty_vertex_buffer(&vk_object->buffer.xyz, size);
  vk_mem_allocator->allocate_empty_stagger_buffer(&vk_object->buffer.xyz_stagger, size);

  size = sizeof(glm::vec4) * max_data;
  vk_mem_allocator->allocate_empty_vertex_buffer(&vk_object->buffer.rgb, size);
  vk_mem_allocator->allocate_empty_stagger_buffer(&vk_object->buffer.rgb_stagger, size);

  size  = sizeof(glm::vec2) * max_data;
  vk_mem_allocator->allocate_empty_vertex_buffer(&vk_object->buffer.uv, size);
  vk_mem_allocator->allocate_empty_stagger_buffer(&vk_object->buffer.uv_stagger, size);

  this->update_buffer(vk_object);

  //---------------------------
}
void Buffer::update_buffer(vk::structure::Object* vk_object){
  utl::type::Data* data = vk_object->data;
  utl::type::Vertice* vertice = data->get_vertice();
  //---------------------------

  if(vertice->xyz.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec3) * vertice->xyz.size();
    vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.xyz, &vk_object->buffer.xyz_stagger, vertice->xyz.data(), data_size);
  }

  if(vertice->rgb.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec4) * vertice->rgb.size();
    vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.rgb, &vk_object->buffer.rgb_stagger, vertice->rgb.data(), data_size);
  }

  if(vertice->uv.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec2) * vertice->uv.size();
    vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.uv, &vk_object->buffer.uv_stagger, vertice->uv.data(), data_size);
  }

  //---------------------------
}

void Buffer::clean_buffers(vk::structure::Object* vk_object){
  //---------------------------

  this->clean_buffer(&vk_object->buffer.xyz);
  this->clean_buffer(&vk_object->buffer.rgb);
  this->clean_buffer(&vk_object->buffer.uv);

  this->clean_buffer(&vk_object->buffer.xyz_stagger);
  this->clean_buffer(&vk_object->buffer.rgb_stagger);
  this->clean_buffer(&vk_object->buffer.uv_stagger);

  //---------------------------
}
void Buffer::clean_buffer(vk::structure::Buffer* buffer){
  //---------------------------

  if(buffer->vbo != VK_NULL_HANDLE){
    vkDestroyBuffer(struct_vulkan->device.handle, buffer->vbo, nullptr);
  }

  if(buffer->mem != VK_NULL_HANDLE){
    vkFreeMemory(struct_vulkan->device.handle, buffer->mem, nullptr);
  }

  //---------------------------
}

//Subfunction
int Buffer::get_size_buffer(vk::structure::Object* vk_object){
  utl::type::Data* data = vk_object->data;
  //---------------------------

  int max_data = 0;
  if(data->nb_data_max != -1){
    max_data = data->nb_data_max;
  }
  else if(data->point.size != -1){
    max_data = data->point.size;
  }
  else if(data->line.size != -1){
    max_data = data->line.size;
  }
  else if(data->triangle.size != -1){
    max_data = data->triangle.size;
  }

  //---------------------------
  return max_data;
}


}
