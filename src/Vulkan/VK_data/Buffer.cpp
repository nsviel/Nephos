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
  //---------------------------

  VkDeviceSize data_size;
  vector<vec3>* xyz;
  vector<vec4>* rgb;
  vector<vec2>* uv;

  switch(data->draw_type){
    case utl::topology::POINT:{
      xyz = &data->point.xyz;
      rgb = &data->point.rgb;
      break;
    }
    case utl::topology::LINE:{
      xyz = &data->line.xyz;
      rgb = &data->line.rgb;
      break;
    }
    case utl::topology::TRIANGLE:{
      xyz = &data->triangle.xyz;
      rgb = &data->triangle.rgb;
      uv = &data->triangle.uv;
      break;
    }
  }

  data_size = sizeof(glm::vec3) * xyz->size();
  vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.xyz, &vk_object->buffer.xyz_stagger, xyz->data(), data_size);

  data_size = sizeof(glm::vec4) * rgb->size();
  vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.rgb, &vk_object->buffer.rgb_stagger, rgb->data(), data_size);

  data_size = sizeof(glm::vec2) * uv->size();
  vk_mem_transfer->copy_data_to_gpu(&vk_object->buffer.uv, &vk_object->buffer.uv_stagger, uv->data(), data_size);

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
