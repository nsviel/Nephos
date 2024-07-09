#include "Layout.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Layout::Layout(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Layout::~Layout(){}

//Main function
void Layout::create_pipeline_layout(vk::structure::Pipeline* pipeline){
  //---------------------------

  //Push constant for MVP matrix
  //VkPushConstantRange pushconstant_range = {};
  //pushconstant_range.stageFlags = TYP_SHADER_VS;
  //pushconstant_range.offset = 0;
  //pushconstant_range.size = sizeof(glm::mat4);

  //Pipeline layout info -> usefull for shader uniform variables
  VkPipelineLayoutCreateInfo pipeline_layout_info{};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts = &pipeline->binding.descriptor.layout;
  //pipeline_layout_info.pushConstantRangeCount = 1;
  //pipeline_layout_info.pPushConstantRanges = &pushconstant_range;

  //Pipeline layout creation
  VkResult result = vkCreatePipelineLayout(vk_struct->device.handle, &pipeline_layout_info, nullptr, &pipeline->layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create pipeline layout!");
  }

  //---------------------------
}
void Layout::clean_pipeline_layout(vk::structure::Pipeline* pipeline){
  //---------------------------

  vkDestroyPipelineLayout(vk_struct->device.handle, pipeline->layout, nullptr);

  //---------------------------
}

}
