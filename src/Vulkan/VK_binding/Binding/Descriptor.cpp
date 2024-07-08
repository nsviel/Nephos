#include "Descriptor.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Descriptor::Descriptor(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);

  //---------------------------
}
Descriptor::~Descriptor(){}

//Main function
void Descriptor::clean_binding(vk::binding::structure::Binding* binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->device.handle, binding->descriptor.layout, nullptr);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

//Descriptor set update
void Descriptor::update_descriptor_uniform(vk::binding::structure::Binding* binding){
  //---------------------------

  //Make list of writeable uniform
  std::vector<VkWriteDescriptorSet> vec_descriptor_write;
  std::vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  for(int i=0; i<binding->vec_uniform.size(); i++){
    vk::binding::structure::Uniform* uniform = binding->vec_uniform[i];

    VkDescriptorBufferInfo descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    vec_descriptor_buffer_info.push_back(descriptor_info);
  }

  for(int i=0; i<binding->vec_uniform.size(); i++){
    vk::binding::structure::Uniform* uniform = binding->vec_uniform[i];
    VkWriteDescriptorSet write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding->descriptor.set;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = TYP_UNIFORM;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &vec_descriptor_buffer_info[i];
    vec_descriptor_write.push_back(write_uniform);
  }

  //Update descriptor
  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(vk_struct->device.handle, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

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
  allocation_info.pSetLayouts = &binding->descriptor.layout;

  VkResult result = vkAllocateDescriptorSets(vk_struct->device.handle, &allocation_info, &binding->descriptor.set);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void Descriptor::create_layout_from_required(vk::binding::structure::Binding* binding){
  std::vector<vk::binding::structure::Required>& vec_required_binding = binding->vec_required_binding;
  //---------------------------

  std::vector<VkDescriptorSetLayoutBinding> vec_binding;
  for(int i=0; i<vec_required_binding.size(); i++){
    vk::binding::structure::Required& req_binding = vec_required_binding[i];

    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding{};
    layout_binding.binding = req_binding.binding;
    layout_binding.descriptorCount = static_cast<uint32_t>(1);
    layout_binding.descriptorType = req_binding.type;
    layout_binding.stageFlags = req_binding.stage;
    layout_binding.pImmutableSamplers = nullptr; // Optional
    vec_binding.push_back(layout_binding);
  }

  //Create descriptor layout from requirements
  binding->descriptor.layout = create_layout(vec_binding);

  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  this->allocate_descriptor_set(binding);
  this->update_descriptor_uniform(binding);

  //---------------------------

}
void Descriptor::make_required_descriptor(utl::base::Data* data, vk::binding::structure::Binding* binding){
  //---------------------------

  vk::binding::structure::Required descriptor = vk_uniform->uniform_mvp();
  binding->vec_required_binding.push_back(vk_uniform->uniform_mvp());

  if(data->topology.type == utl::topology::POINT){
    vk::binding::structure::Required descriptor = vk_uniform->uniform_point_size();
    binding->vec_required_binding.push_back(vk_uniform->uniform_point_size());
  }

  //---------------------------

}

VkDescriptorSetLayout Descriptor::create_layout(std::vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Descriptor set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(vk_struct->device.handle, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
  return descriptor_layout;
}

}
