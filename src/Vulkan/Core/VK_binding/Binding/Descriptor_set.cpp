#include "Descriptor_set.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Descriptor_set::Descriptor_set(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);

  //---------------------------
}
Descriptor_set::~Descriptor_set(){}

//Main function
void Descriptor_set::allocate_descriptor_set(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout){
  //---------------------------
say("----");
  this->allocate_handle(descriptor_set, layout);
  this->create_descriptor(descriptor_set, layout);
  this->update_descriptor_set(descriptor_set, layout);

  //---------------------------
}
void Descriptor_set::clean_descriptor_set(vk::descriptor::structure::Descriptor_set& descriptor_set){
  //---------------------------

  this->free_handle(descriptor_set);
  vk_uniform->clean_uniform(descriptor_set);

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
void Descriptor_set::free_handle(vk::descriptor::structure::Descriptor_set& descriptor_set){
  //---------------------------

  vkFreeDescriptorSets(vk_struct->core.device.handle, vk_struct->core.pools.descriptor_set.pool, 1, &descriptor_set.handle);

  //---------------------------
}
void Descriptor_set::create_descriptor(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout){
  //---------------------------

  for(auto& descriptor : layout.vec_descriptor){

    switch(descriptor.type){
      case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:{
        vk_sampler->create_sampler(descriptor_set, descriptor);
        break;
      }
      case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:{
        vk_uniform->create_uniform(descriptor_set, descriptor);
        break;
      }
    }

  }

  //---------------------------
}
void Descriptor_set::update_descriptor_set(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout){
  //---------------------------

  vk_uniform->actualize_uniform(descriptor_set);

  //---------------------------
}
void Descriptor_set::bind_descriptor_set(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline, vk::descriptor::structure::Descriptor_set& descriptor_set){
  //---------------------------

  vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 1, &descriptor_set.handle, 0, nullptr);

  //---------------------------
}

}
