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
void Layout::create_layout(vk::binding::structure::Layout& layout){
  //---------------------------

  std::vector<VkDescriptorSetLayoutBinding> vec_binding;
  this->make_required_binding(layout, vec_binding);
  this->create_layout_object(layout, vec_binding);

  //---------------------------
}
void Layout::clean_layout(vk::binding::structure::Layout& layout){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->core.device.handle, layout.handle, nullptr);

  //---------------------------
}

//Subfunction
void Layout::make_required_binding(vk::binding::structure::Layout& layout, std::vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  for(auto& descriptor : layout.vec_descriptor){
    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding{};
    layout_binding.binding = descriptor.binding;
    layout_binding.descriptorCount = static_cast<uint32_t>(1);
    layout_binding.descriptorType = descriptor.type;
    layout_binding.stageFlags = descriptor.stage;
    layout_binding.pImmutableSamplers = nullptr; // Optional

    vec_binding.push_back(layout_binding);
  }

  //---------------------------
}
void Layout::create_layout_object(vk::binding::structure::Layout& layout, std::vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Layout set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(vk_struct->core.device.handle, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  layout.handle = descriptor_layout;

  //---------------------------
}

}
