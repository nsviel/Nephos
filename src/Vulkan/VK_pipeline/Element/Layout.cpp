#include "Layout.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Layout::Layout(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_shader = new vk::pipeline::Shader(vk_struct);
  this->vk_data = new vk::pipeline::Data(vk_struct);
  this->vk_element = new vk::pipeline::Element(vk_struct);

  //---------------------------
}
Layout::~Layout(){}

//Main function
void Layout::clean_pipeline_layout(vk::structure::Pipeline* pipeline){
  //---------------------------

  vkDestroyPipelineLayout(vk_struct->device.handle, pipeline->layout, nullptr);

  //---------------------------
}
void Layout::clean_pipeline_handle(vk::structure::Pipeline* pipeline){
  //---------------------------

  vkDestroyPipeline(vk_struct->device.handle, pipeline->handle, nullptr);

  //---------------------------
}

//Pipeline creation / cleaning
void Layout::create_pipeline_handle(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline->info.shader_stage.size());
  pipeline_info.pStages = pipeline->info.shader_stage.data();
  pipeline_info.pVertexInputState = &pipeline->info.vertex_input_info;
  pipeline_info.pInputAssemblyState = &pipeline->info.input_assembly;
  pipeline_info.pViewportState = &pipeline->info.viewport_state;
  pipeline_info.pRasterizationState = &pipeline->info.rasterizer;
  pipeline_info.pMultisampleState = &pipeline->info.multisampling;
  pipeline_info.pDepthStencilState = &pipeline->info.depth_stencil;
  pipeline_info.pColorBlendState = &pipeline->info.color_blend_info;
  pipeline_info.pDynamicState = &pipeline->info.dynamic_state;
  pipeline_info.layout = pipeline->layout;
  pipeline_info.renderPass = renderpass->handle;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipeline_info.basePipelineIndex = -1; // Optional
  pipeline->info.info = pipeline_info;

  VkResult result = vkCreateGraphicsPipelines(vk_struct->device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline->handle);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //---------------------------
}
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

}
