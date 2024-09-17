#include "Descriptor_set.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Descriptor_set::Descriptor_set(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Descriptor_set::~Descriptor_set(){}

//Main function
void Descriptor_set::allocate_descriptor_set(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout){
  //---------------------------

  this->allocate_handle(descriptor_set, layout);
  this->update_descriptor_set(descriptor_set, layout);

  //---------------------------
}
void Descriptor_set::bind_descriptor_set(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline, VkDescriptorSet descriptor_set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 1, &descriptor_set, 0, nullptr);

  //---------------------------
}
void Descriptor_set::update_descriptor_set(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout){
  //---------------------------

  //CLear description vectors
  descriptor_set.vec_descriptor_write.clear();
  descriptor_set.vec_descriptor_buffer_info.clear();

  //Make list of writeable uniform
  for(auto& [name, uniform] : layout.map_uniform){
    //Blabla
    VkDescriptorBufferInfo descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    descriptor_set.vec_descriptor_buffer_info.push_back(descriptor_info);

    //Blabla
    VkWriteDescriptorSet write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = descriptor_set.handle;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_set.vec_descriptor_buffer_info.back();
    descriptor_set.vec_descriptor_write.push_back(write_uniform);
  }

  //Update descriptor
  if(!descriptor_set.vec_descriptor_write.empty()){
    vkUpdateDescriptorSets(vk_struct->core.device.handle, static_cast<uint32_t>(descriptor_set.vec_descriptor_write.size()), descriptor_set.vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void Descriptor_set::clean_descriptor_set(vk::descriptor::structure::Descriptor_set& descriptor_set){
  //---------------------------

  vkFreeDescriptorSets(vk_struct->core.device.handle, vk_struct->core.pools.descriptor_set.pool, 1, &descriptor_set.handle);

  //---------------------------
}

//Subfunction
void Descriptor_set::allocate_handle(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout){
  //---------------------------

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = vk_struct->core.pools.descriptor_set.pool;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &layout.handle;

  VkResult result = vkAllocateDescriptorSets(vk_struct->core.device.handle, &allocation_info, &descriptor_set.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}

}
