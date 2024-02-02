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
  //---------------------------

  //Find buffer size
  int nb_data = vk_object->data->xyz.size();
  int nb_data_max = vk_object->data->nb_data_max;
  if(nb_data == 0 && nb_data_max == -1) return;
  int max_data = (vk_object->data->nb_data_max == -1) ? vk_object->data->xyz.size() : vk_object->data->nb_data_max;


  VkDeviceSize buffer_size;
  buffer_size = sizeof(glm::vec3) * max_data;
  vk_memory->create_empty_buffer(&vk_object->xyz, buffer_size);
  buffer_size = sizeof(glm::vec4) * max_data;
  vk_memory->create_empty_buffer(&vk_object->rgb, buffer_size);
  buffer_size = sizeof(glm::vec2) * max_data;
  vk_memory->create_empty_buffer(&vk_object->uv, buffer_size);



  if(vk_object->data->xyz.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec3) * vk_object->data->xyz.size();
    vk_memory->fill_buffer_data(&vk_object->xyz, vk_object->data->xyz.data(), data_size);
  }

  if(vk_object->data->rgb.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec4) * vk_object->data->rgb.size();
    vk_memory->fill_buffer_data(&vk_object->rgb, vk_object->data->rgb.data(), data_size);
  }

  if(vk_object->data->uv.size() != 0){
    VkDeviceSize data_size = sizeof(glm::vec2) * vk_object->data->uv.size();
    vk_memory->fill_buffer_data(&vk_object->uv, vk_object->data->uv.data(), data_size);
  }



  //---------------------------
}
void Buffer::update_buffer(vk::structure::Object* vk_object){
  //---------------------------

  vk_memory->update_buffer_to_gpu(vk_object->data->xyz, &vk_object->xyz);
  vk_memory->update_buffer_to_gpu(vk_object->data->rgb, &vk_object->rgb);
  vk_memory->update_buffer_to_gpu(vk_object->data->uv,  &vk_object->uv);

  //---------------------------
}
void Buffer::create_or_update_buffer(vk::structure::Object* vk_object){
  //---------------------------

  //A VIRER PUISQUEON VA CREER DES BUFFER DE TAILLE FIXE et quon fill après

  if(vk_object->xyz.vbo == VK_NULL_HANDLE){
    //vk_object->xyz.max_data = vk_object->data->nb_data_max;
    //vk_memory->create_buffer_to_gpu(vk_object->data->xyz, &vk_object->xyz);
  }else{
    //vk_memory->update_buffer_to_gpu(vk_object->data->xyz, &vk_object->xyz);
  }

  if(vk_object->rgb.vbo == VK_NULL_HANDLE){
    //vk_object->rgb.max_data = vk_object->data->nb_data_max;
    //vk_memory->create_buffer_to_gpu(vk_object->data->rgb, &vk_object->rgb);
  }else{
    //vk_memory->update_buffer_to_gpu(vk_object->data->rgb, &vk_object->rgb);
  }

  if(vk_object->uv.vbo == VK_NULL_HANDLE){
    //vk_object->uv.max_data  = vk_object->data->nb_data_max;
    //vk_memory->create_buffer_to_gpu(vk_object->data->uv, &vk_object->uv);
  }else{
    //vk_memory->update_buffer_to_gpu(vk_object->data->uv, &vk_object->uv);
  }

  //---------------------------
}

void Buffer::clean_buffers(vk::structure::Object* vk_object){
  //---------------------------

  this->clean_buffer(&vk_object->xyz);
  this->clean_buffer(&vk_object->rgb);
  this->clean_buffer(&vk_object->uv);

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
