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
void Uniform::create_uniform(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Descriptor& descriptor){
  //---------------------------

  std::shared_ptr<vk::descriptor::structure::Uniform> uniform = std::make_shared<vk::descriptor::structure::Uniform>();
  uniform->name = descriptor.name;
  uniform->binding = descriptor.binding;
  uniform->size = descriptor.size;

  vk_mem_allocator->create_gpu_buffer(uniform->size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
  vk_mem_allocator->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
  VkResult result = vkMapMemory(vk_struct->core.device.handle, uniform->mem, 0, uniform->size, 0, &uniform->mapped);
  if (result != VK_SUCCESS) {
    std::cout<<"[error] Ici ça merde"<<std::endl;
  }

  descriptor_set.map_uniform[descriptor.name] = std::move(uniform);

  //---------------------------
}
void Uniform::actualize_uniform(vk::descriptor::structure::Descriptor_set& descriptor_set){
  VkDeviceSize alignment = vk_struct->core.device.physical_device.properties.limits.minUniformBufferOffsetAlignment;
  //---------------------------

  descriptor_set.vec_descriptor_buffer_info.clear();
  descriptor_set.vec_write_descriptor_set.clear();

  //Make list of writeable uniform
  for(auto& [name, uniform] : descriptor_set.map_uniform){
    if (uniform->buffer == VK_NULL_HANDLE) {
      std::cout<<"[error] Invalid VkBuffer handle"<<std::endl;
    }

    //Descriptor buffer info
    VkDescriptorBufferInfo descriptor_info{};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    descriptor_set.vec_descriptor_buffer_info.push_back(descriptor_info);

    //Write descriptor info
    VkWriteDescriptorSet write_uniform{};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = descriptor_set.handle;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_set.vec_descriptor_buffer_info.back();
    descriptor_set.vec_write_descriptor_set.push_back(write_uniform);
  }

  //Update descriptor
  if(!descriptor_set.vec_write_descriptor_set.empty()){
    vkUpdateDescriptorSets(vk_struct->core.device.handle, static_cast<uint32_t>(descriptor_set.vec_write_descriptor_set.size()), descriptor_set.vec_write_descriptor_set.data(), 0, nullptr);
  }

  //Dunno why but need to wait few ms here
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  //---------------------------
}
void Uniform::clean_uniform(vk::descriptor::structure::Descriptor_set& descriptor_set){
  //---------------------------

  for(auto& [name, uniform] : descriptor_set.map_uniform){
    vkDestroyBuffer(vk_struct->core.device.handle, uniform->buffer, nullptr);
    vkFreeMemory(vk_struct->core.device.handle, uniform->mem, nullptr);
  }

  //---------------------------
}

}
