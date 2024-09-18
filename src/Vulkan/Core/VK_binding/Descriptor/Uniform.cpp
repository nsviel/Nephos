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
  vkMapMemory(vk_struct->core.device.handle, uniform->mem, 0, uniform->size, 0, &uniform->mapped);

  descriptor_set.map_uniform[descriptor.name] = std::move(uniform);

  //---------------------------
}
void Uniform::actualize_uniform(vk::descriptor::structure::Descriptor_set& descriptor_set){
  VkDeviceSize alignment = vk_struct->core.device.physical_device.properties.limits.minUniformBufferOffsetAlignment;
  //---------------------------

  //Associated descriptor descriptions
  std::vector<VkWriteDescriptorSet> vec_write_descriptor_set;
  std::vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;

  //Make list of writeable uniform
  std::size_t previous_size = 0;
  for(auto& [name, uniform] : descriptor_set.map_uniform){
    if (uniform->buffer == VK_NULL_HANDLE) {
      throw std::runtime_error("Invalid VkBuffer handle.");
    }

    //Descriptor buffer info
    VkDescriptorBufferInfo descriptor_info{};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = previous_size;
    descriptor_info.range = uniform->size;
    vec_descriptor_buffer_info.push_back(descriptor_info);
    //previous_size = uniform->size;

    //Write descriptor info
    VkWriteDescriptorSet write_uniform{};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = descriptor_set.handle;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_info;
    vec_write_descriptor_set.push_back(write_uniform);
  }

  //Update descriptor
  if(!vec_write_descriptor_set.empty()){
    vkUpdateDescriptorSets(vk_struct->core.device.handle, static_cast<uint32_t>(vec_write_descriptor_set.size()), vec_write_descriptor_set.data(), 0, nullptr);
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
