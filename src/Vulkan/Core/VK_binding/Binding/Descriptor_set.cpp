#include "Descriptor_set.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Descriptor_set::Descriptor_set(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Descriptor_set::~Descriptor_set(){}

//Main function
void Descriptor_set::allocate(vk::binding::structure::Binding& binding){
  //---------------------------

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = vk_struct->core.pools.descriptor.allocator;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &binding.layout.handle;

  VkResult result = vkAllocateDescriptorSets(vk_struct->core.device.handle, &allocation_info, &binding.descriptor_set.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  this->update(binding);

  //---------------------------
}
void Descriptor_set::bind(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->layout, 0, 1, &set, 0, nullptr);

  //---------------------------
}
void Descriptor_set::update(vk::binding::structure::Binding& binding){
  //---------------------------

  //Make list of writeable uniform
  std::vector<VkWriteDescriptorSet> vec_descriptor_write;
  std::vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  for(auto& [name, uniform] : binding.layout.map_uniform){
    //Blabla
    VkDescriptorBufferInfo descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    vec_descriptor_buffer_info.push_back(descriptor_info);

    //Blabla
    VkWriteDescriptorSet write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding.descriptor_set.handle;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_info;
    vec_descriptor_write.push_back(write_uniform);
  }

  //Update descriptor
  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(vk_struct->core.device.handle, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void Descriptor_set::clean(vk::binding::structure::Binding& binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->core.device.handle, binding.layout.handle, nullptr);

  //---------------------------
}

}
