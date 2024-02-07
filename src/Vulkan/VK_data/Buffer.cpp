#include "Buffer.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Buffer::Buffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_memory = new vk::command::Memory(struct_vulkan);

  //---------------------------
}
Buffer::~Buffer(){}

//Main function
void Buffer::create_buffers(vk::structure::Object* vk_object){
  VkDeviceSize size;
  //---------------------------

  //Check for buffer creation validity
  utl::type::Data* data = vk_object->data;
  if(data->nb_point == -1) data->nb_point = data->xyz.size();
  if(data->nb_point == 0 && data->nb_data_max == -1) return;
  int max_data = (data->nb_data_max == -1) ? data->nb_point : data->nb_data_max;

  //Find buffer size
  size = sizeof(glm::vec3) * max_data;
  vk_memory->create_empty_vertex_buffer(&vk_object->buffer.xyz, size);
  vk_memory->create_empty_stagger_buffer(&vk_object->buffer.xyz_stagger, size);

  size = sizeof(glm::vec4) * max_data;
  vk_memory->create_empty_vertex_buffer(&vk_object->buffer.rgb, size);
  vk_memory->create_empty_stagger_buffer(&vk_object->buffer.rgb_stagger, size);

  size  = sizeof(glm::vec2) * max_data;
  vk_memory->create_empty_vertex_buffer(&vk_object->buffer.uv, size);
  vk_memory->create_empty_stagger_buffer(&vk_object->buffer.uv_stagger, size);

  this->update_buffer(vk_object);

  //---------------------------
}
void Buffer::update_buffer(vk::structure::Object* vk_object){
  //---------------------------

  if(vk_object->data->xyz.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec3) * vk_object->data->xyz.size();
    //vk_memory->update_buffer_data(&vk_object->buffer.xyz, &vk_object->buffer.xyz_stagger, vk_object->data->xyz.data(), data_size);
    vk_memory->update_buffer_data(&vk_object->buffer.xyz, vk_object->data->xyz.data(), data_size);
  }

  if(vk_object->data->rgb.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec4) * vk_object->data->rgb.size();
    //vk_memory->update_buffer_data(&vk_object->buffer.rgb, &vk_object->buffer.rgb_stagger, vk_object->data->rgb.data(), data_size);
    vk_memory->update_buffer_data(&vk_object->buffer.rgb, vk_object->data->rgb.data(), data_size);
  }

  if(vk_object->data->uv.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec2) * vk_object->data->uv.size();
    //vk_memory->update_buffer_data(&vk_object->buffer.uv, &vk_object->buffer.uv_stagger, vk_object->data->uv.data(), data_size);
    vk_memory->update_buffer_data(&vk_object->buffer.uv, vk_object->data->uv.data(), data_size);
  }

  //---------------------------
}
void Buffer::update_buffer_test(vk::structure::Object* vk_object){
  //---------------------------

  VkDeviceSize data_size = sizeof(glm::vec3) * vk_object->data->xyz.size();
  vk_memory->update_buffer_data(&vk_object->buffer.xyz, &vk_object->buffer.xyz_stagger, vk_object->data->xyz.data(), data_size);


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
    vkDestroyBuffer(struct_vulkan->device.device, buffer->vbo, nullptr);
  }

  if(buffer->mem != VK_NULL_HANDLE){
    vkFreeMemory(struct_vulkan->device.device, buffer->mem, nullptr);
  }

  //---------------------------
}

}
