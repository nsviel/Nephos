#include "Descriptor.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Descriptor::Descriptor(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);
  this->vk_layout = new vk::binding::Layout(vk_struct);

  //---------------------------
}
Descriptor::~Descriptor(){}

//Main function
void Descriptor::create_binding(vk::binding::structure::Binding* binding){
  //---------------------------

  vk_layout->create_layout(binding);
  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  this->allocate_descriptor_set(binding);
  vk_uniform->update_uniform(binding);

  //---------------------------
}
void Descriptor::clean_binding(vk::binding::structure::Binding* binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->device.handle, binding->descriptor_set.layout, nullptr);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

//Subfunction
void Descriptor::cmd_bind_descriptor(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, TYP_BIND_PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &set, 0, nullptr);

  //---------------------------
}
void Descriptor::allocate_descriptor_set(vk::binding::structure::Binding* binding){
  //---------------------------

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = vk_struct->pools.descriptor.allocator;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &binding->descriptor_set.layout;

  VkResult result = vkAllocateDescriptorSets(vk_struct->device.handle, &allocation_info, &binding->descriptor_set.set);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void Descriptor::make_required_descriptor(utl::base::Data& data, vk::binding::structure::Binding* binding){
  //---------------------------

  vk::binding::structure::Descriptor descriptor = vk_uniform->uniform_mvp();
  binding->vec_required_binding.push_back(vk_uniform->uniform_mvp());

  if(data.topology.type == utl::topology::POINT){
    vk::binding::structure::Descriptor descriptor = vk_uniform->uniform_point_size();
    binding->vec_required_binding.push_back(vk_uniform->uniform_point_size());
  }

  //---------------------------

}

}
