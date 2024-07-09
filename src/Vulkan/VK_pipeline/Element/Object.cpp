#include "Object.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Object::Object(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_shader = new vk::shader::Shader(vk_struct);
  this->vk_data = new vk::pipeline::Data(vk_struct);

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::create_pipeline_object(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  this->info_pipeline_topology(pipeline);
  this->find_pipeline_dynamic_state(pipeline);
  this->find_pipeline_viewport_state(pipeline);
  this->find_pipeline_rasterization_state(pipeline);
  this->find_pipeline_multisampling_state(pipeline);
  this->find_pipeline_blend_attachment_state(pipeline);
  this->find_pipeline_blend_state(pipeline);
  this->find_pipeline_depth_state(pipeline);
  this->create_pipeline_handle(renderpass, pipeline);

  //---------------------------
}

//Subfunction
void Object::info_pipeline_topology(vk::structure::Pipeline* pipeline){
  //---------------------------

  info_topology = {};
  info_topology.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  info_topology.primitiveRestartEnable = VK_FALSE;

  switch(pipeline->info.topology){
    case utl::topology::POINT:{
      info_topology.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
      break;
    }
    case utl::topology::LINE:{
      info_topology.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
      break;
    }
    case utl::topology::TRIANGLE:{
      info_topology.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
      break;
    }
  }

  //---------------------------
}
void Object::find_pipeline_dynamic_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  static std::vector<VkDynamicState> dynamic_state_object;
  dynamic_state_object.clear();
  dynamic_state_object.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  dynamic_state_object.push_back(VK_DYNAMIC_STATE_SCISSOR);
  dynamic_state_object.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);

  //Dynamic internal variables (viewport, line width, ...)
  //the subsequent values has to be given at runtime
  VkPipelineDynamicStateCreateInfo dynamic_state{};
  dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state.dynamicStateCount = static_cast<uint32_t>(dynamic_state_object.size());
  dynamic_state.pDynamicStates = dynamic_state_object.data();

  //---------------------------
  pipeline->element.dynamic_state = dynamic_state;
}
void Object::find_pipeline_viewport_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  //Viewport info
  VkPipelineViewportStateCreateInfo viewport_state{};
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &vk_struct->render.viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &vk_struct->render.scissor;

  //---------------------------
  pipeline->element.viewport_state = viewport_state;
}
void Object::find_pipeline_rasterization_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  //---------------------------
  pipeline->element.rasterizer = rasterizer;
}
void Object::find_pipeline_multisampling_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = vk_struct->device.physical_device.max_sample_count;
  multisampling.minSampleShading = 1.0f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  //---------------------------
  pipeline->element.multisampling = multisampling;
}
void Object::find_pipeline_depth_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  VkPipelineDepthStencilStateCreateInfo depth_stencil = {};
  depth_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depth_stencil.depthTestEnable = (pipeline->info.shader->with_depth_test) ? VK_TRUE : VK_FALSE;
  depth_stencil.depthWriteEnable = (pipeline->info.shader->with_depth_test) ? VK_TRUE : VK_FALSE;
  depth_stencil.depthCompareOp = VK_COMPARE_OP_LESS;
  depth_stencil.depthBoundsTestEnable = VK_FALSE;
  depth_stencil.minDepthBounds = 0.0f; // Optional
  depth_stencil.maxDepthBounds = 1.0f; // Optional
  depth_stencil.stencilTestEnable = VK_FALSE;
  depth_stencil.front = {}; // Optional
  depth_stencil.back = {}; // Optional

  //---------------------------
  pipeline->element.depth_stencil = depth_stencil;
}
void Object::find_pipeline_blend_attachment_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  VkPipelineColorBlendAttachmentState color_blend_attachment{};
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_TRUE;
  color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; // Optional
  color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; // Optional
  color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  //---------------------------

  pipeline->element.color_blend_attachment = color_blend_attachment;
}
void Object::find_pipeline_blend_state(vk::structure::Pipeline* pipeline){
  //---------------------------

  VkPipelineColorBlendStateCreateInfo color_blend_info{};
  color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blend_info.logicOpEnable = VK_FALSE;
  color_blend_info.logicOp = VK_LOGIC_OP_COPY; // Optional
  color_blend_info.attachmentCount = 1;
  color_blend_info.pAttachments = &pipeline->element.color_blend_attachment;
  color_blend_info.blendConstants[0] = 0.0f; // Optional
  color_blend_info.blendConstants[1] = 0.0f; // Optional
  color_blend_info.blendConstants[2] = 0.0f; // Optional
  color_blend_info.blendConstants[3] = 0.0f; // Optional

  //---------------------------
  pipeline->element.color_blend_info = color_blend_info;
}

void Object::create_pipeline_handle(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline->element.shader_stage.size());
  pipeline_info.pStages = pipeline->element.shader_stage.data();
  pipeline_info.pVertexInputState = &pipeline->element.vertex_input_info;
  pipeline_info.pInputAssemblyState = &info_topology;
  pipeline_info.pViewportState = &pipeline->element.viewport_state;
  pipeline_info.pRasterizationState = &pipeline->element.rasterizer;
  pipeline_info.pMultisampleState = &pipeline->element.multisampling;
  pipeline_info.pDepthStencilState = &pipeline->element.depth_stencil;
  pipeline_info.pColorBlendState = &pipeline->element.color_blend_info;
  pipeline_info.pDynamicState = &pipeline->element.dynamic_state;
  pipeline_info.layout = pipeline->layout;
  pipeline_info.renderPass = renderpass->handle;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipeline_info.basePipelineIndex = -1; // Optional

  VkResult result = vkCreateGraphicsPipelines(vk_struct->device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline->handle);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //---------------------------
}

}
