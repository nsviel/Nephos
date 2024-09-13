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
  allocation_info.descriptorPool = vk_struct->pools.descriptor.allocator;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &binding.descriptor_set.layout;

  VkResult result = vkAllocateDescriptorSets(vk_struct->device.handle, &allocation_info, &binding.descriptor_set.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void Descriptor_set::bind(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, TYP_BIND_PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &set, 0, nullptr);

  //---------------------------
}
void Descriptor_set::clean(vk::binding::structure::Binding& binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->device.handle, binding.descriptor_set.layout, nullptr);

  //---------------------------
}

}
