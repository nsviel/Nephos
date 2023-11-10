#include "VK_binding.h"

#include <VK_binding/VK_uniform.h>
#include <VK_binding/VK_sampler.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_binding::VK_binding(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_descriptor = new VK_descriptor(struct_vulkan);
  this->vk_uniform = new VK_uniform(struct_vulkan);
  this->vk_sampler = new VK_sampler(struct_vulkan);

  //---------------------------
}
VK_binding::~VK_binding(){}

//Main function
void VK_binding::create_binding(Struct_binding* binding){
  //---------------------------

  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  vk_descriptor->allocate_descriptor_set(binding);
  vk_descriptor->update_descriptor_uniform(binding);

  //---------------------------
}
void VK_binding::clean_binding(Struct_binding* binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(struct_vulkan->device.device, binding->descriptor.layout, nullptr);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}
