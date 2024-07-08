#include "Layout.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Layout::Layout(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Layout::~Layout(){}

//Main function
void Layout::create_layout(vk::binding::structure::Binding* binding){
  std::vector<vk::binding::structure::Required>& vec_required_binding = binding->vec_required_binding;
  //---------------------------

  std::vector<VkDescriptorSetLayoutBinding> vec_binding;
  this->make_required_binding(binding, vec_binding);
  this->create_layout(binding, vec_binding);

  //---------------------------
}
void Layout::clean_layout(vk::binding::structure::Binding* binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->device.handle, binding->descriptor.layout, nullptr);

  //---------------------------
}

//Subfunction
void Layout::make_required_binding(vk::binding::structure::Binding* binding, std::vector<VkDescriptorSetLayoutBinding>& vec_binding){
  std::vector<vk::binding::structure::Required>& vec_required_binding = binding->vec_required_binding;
  //---------------------------

  for(int i=0; i<vec_required_binding.size(); i++){
    vk::binding::structure::Required& required = vec_required_binding[i];

    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding{};
    layout_binding.binding = required.binding;
    layout_binding.descriptorCount = static_cast<uint32_t>(1);
    layout_binding.descriptorType = required.type;
    layout_binding.stageFlags = required.stage;
    layout_binding.pImmutableSamplers = nullptr; // Optional
    vec_binding.push_back(layout_binding);
  }

  //---------------------------
}
void Layout::create_layout(vk::binding::structure::Binding* binding, std::vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Layout set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(vk_struct->device.handle, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  binding->descriptor.layout = descriptor_layout;

  //---------------------------
}

}
