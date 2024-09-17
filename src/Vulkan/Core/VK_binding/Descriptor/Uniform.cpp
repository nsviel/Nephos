#include "Uniform.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Uniform::Uniform(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);

  //---------------------------
}
Uniform::~Uniform(){}

//Uniform creation
void Uniform::create_uniform(vk::descriptor::structure::Layout& layout, vk::descriptor::structure::Descriptor& descriptor){
  //---------------------------

  std::shared_ptr<vk::descriptor::structure::Uniform> uniform = std::make_shared<vk::descriptor::structure::Uniform>();
  uniform->name = descriptor.name;
  uniform->binding = descriptor.binding;
  uniform->size = descriptor.size;

  vk_mem_allocator->create_gpu_buffer(uniform->size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
  vkMapMemory(vk_struct->core.device.handle, uniform->mem, 0, uniform->size, 0, &uniform->mapped);

  layout.map_uniform[descriptor.name] = std::move(uniform);

  //---------------------------
}
void Uniform::insert_uniform(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Uniform& uniform){
  //---------------------------

  //Blabla
  VkDescriptorBufferInfo descriptor_info = {};
  descriptor_info.buffer = uniform.buffer;
  descriptor_info.offset = 0;
  descriptor_info.range = uniform.size;

  //Blabla
  VkWriteDescriptorSet write_uniform = {};
  write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  write_uniform.dstSet = descriptor_set.handle;
  write_uniform.dstBinding = uniform.binding;
  write_uniform.dstArrayElement = 0;
  write_uniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  write_uniform.descriptorCount = 1;
  write_uniform.pBufferInfo = &descriptor_info;

  vkUpdateDescriptorSets(vk_struct->core.device.handle, 1, &write_uniform, 0, nullptr);

  //---------------------------
}
void Uniform::clean_uniform(vk::descriptor::structure::Layout& layout){
  //---------------------------

  for(auto& [name, uniform] : layout.map_uniform){
    vkDestroyBuffer(vk_struct->core.device.handle, uniform->buffer, nullptr);
    vkFreeMemory(vk_struct->core.device.handle, uniform->mem, nullptr);
  }

  //---------------------------
}

}
