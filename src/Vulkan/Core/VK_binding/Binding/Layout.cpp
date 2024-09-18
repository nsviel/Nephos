#include "Layout.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::descriptor{

//Constructor / Destructor
Layout::Layout(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Layout::~Layout(){}

//Main function
void Layout::create_layout(vk::descriptor::structure::Layout& layout){
  //---------------------------

  this->make_required_binding(layout);
  this->create_layout_object(layout);

  //---------------------------
}
void Layout::clean_layout(vk::descriptor::structure::Layout& layout){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_struct->core.device.handle, layout.handle, nullptr);

  //---------------------------
}

//Subfunction
void Layout::make_required_binding(vk::descriptor::structure::Layout& layout){
  layout.vec_binding.clear();
  //---------------------------

  for(auto& descriptor : layout.vec_descriptor){
    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding{};
    layout_binding.binding = descriptor.binding;
    layout_binding.descriptorCount = static_cast<uint32_t>(1);
    layout_binding.descriptorType = descriptor.type;
    layout_binding.stageFlags = descriptor.stage;
    layout_binding.pImmutableSamplers = nullptr; // Optional

    layout.vec_binding.push_back(layout_binding);
  }

  //---------------------------
}
void Layout::create_layout_object(vk::descriptor::structure::Layout& layout){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layout_info{};
  layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layout_info.bindingCount = static_cast<uint32_t>(layout.vec_binding.size());
  layout_info.pBindings = layout.vec_binding.data();

  //Layout set layout creation
  VkResult result = vkCreateDescriptorSetLayout(vk_struct->core.device.handle, &layout_info, nullptr, &layout.handle);
  if(result != VK_SUCCESS){
    std::cout<<"[error] failed to create descriptor set layout"<<std::endl;
  }

  //---------------------------
}

}
