#include "Component.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Component::Component(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_descriptor = new vk::pipeline::Descriptor(vk_struct);
  this->vk_shader = new vk::pipeline::Shader(vk_struct);
  this->vk_vertex = new vk::pipeline::Vertex(vk_struct);
  this->vk_layout = new vk::pipeline::Layout(vk_struct);

  //---------------------------
}
Component::~Component(){}

//Main function
void Component::create_pipeline_object(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  //Pipeline attribut description
  vk_descriptor->create_pipeline_descriptor(pipeline);
  vk_shader->create_pipeline_shader(pipeline);
  vk_vertex->pipeline_vertex_description(pipeline);
  vk_layout->create_pipeline_layout(pipeline);

  this->info_pipeline_topology(pipeline);
  this->info_pipeline_dynamic(pipeline);
  this->info_pipeline_viewport(pipeline);
  this->info_pipeline_rasterization(pipeline);
  this->info_pipeline_multisampling(pipeline);
  this->info_pipeline_blend_attachment(pipeline);
  this->info_pipeline_blend(pipeline);
  this->info_pipeline_depth_stencil(pipeline);

  //Pipeline creation
  this->create_pipeline_handle(renderpass, pipeline);
  vk_shader->clean_pipeline_shader(pipeline);

  //---------------------------
}
void Component::clean_pipeline_object(vk::structure::Pipeline& pipeline){
  //---------------------------

  this->clean_pipeline_handle(pipeline);
  vk_layout->clean_pipeline_layout(pipeline);
  vk_descriptor->clean_pipeline_descriptor(pipeline);

  //---------------------------
}

//Subfunction
void Component::info_pipeline_topology(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineInputAssemblyStateCreateInfo topology{};
  topology.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  topology.primitiveRestartEnable = VK_FALSE;

  switch(pipeline.info.topology){
    case utl::topology::POINT:{
      topology.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
      break;
    }
    case utl::topology::LINE:{
      topology.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
      break;
    }
    case utl::topology::TRIANGLE:{
      topology.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
      break;
    }
  }

  //---------------------------
  pipeline.component.topology = topology;
}
void Component::info_pipeline_dynamic(vk::structure::Pipeline& pipeline){
  //---------------------------

  std::vector<VkDynamicState>& vec_dynamic_state = pipeline.component.vec_dynamic_state;
  vec_dynamic_state.clear();
  vec_dynamic_state.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  vec_dynamic_state.push_back(VK_DYNAMIC_STATE_SCISSOR);
  vec_dynamic_state.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);

  //Dynamic internal variables (viewport, line width, ...)
  VkPipelineDynamicStateCreateInfo dynamic{};
  dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic.dynamicStateCount = static_cast<uint32_t>(vec_dynamic_state.size());
  dynamic.pDynamicStates = vec_dynamic_state.data();

  //---------------------------
  pipeline.component.dynamic = dynamic;
}
void Component::info_pipeline_viewport(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Viewport info
  VkPipelineViewportStateCreateInfo viewport{};
  viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport.viewportCount = 1;
  viewport.pViewports = &vk_struct->core.viewport.handle;
  viewport.scissorCount = 1;
  viewport.pScissors = &vk_struct->core.viewport.scissor;

  //---------------------------
  pipeline.component.viewport = viewport;
}
void Component::info_pipeline_rasterization(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineRasterizationStateCreateInfo rasterization{};
  rasterization.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterization.depthClampEnable = VK_FALSE;
  rasterization.rasterizerDiscardEnable = VK_FALSE;
  rasterization.polygonMode = VK_POLYGON_MODE_FILL;
  rasterization.lineWidth = 1.0f;
  rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterization.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  rasterization.depthBiasEnable = VK_FALSE;
  rasterization.depthBiasConstantFactor = 0.0f; // Optional
  rasterization.depthBiasClamp = 0.0f; // Optional
  rasterization.depthBiasSlopeFactor = 0.0f; // Optional

  //---------------------------
  pipeline.component.rasterization = rasterization;
}
void Component::info_pipeline_multisampling(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineMultisampleStateCreateInfo multisample{};
  multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisample.sampleShadingEnable = VK_FALSE;
  multisample.rasterizationSamples = vk_struct->core.device.physical_device.max_sample_count;
  multisample.minSampleShading = 1.0f; // Optional
  multisample.pSampleMask = nullptr; // Optional
  multisample.alphaToCoverageEnable = VK_FALSE; // Optional
  multisample.alphaToOneEnable = VK_FALSE; // Optional

  //---------------------------
  pipeline.component.multisample = multisample;
}
void Component::info_pipeline_blend_attachment(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineColorBlendAttachmentState blend_attachment{};
  blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  blend_attachment.blendEnable = VK_TRUE;
  blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; // Optional
  blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; // Optional
  blend_attachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  //---------------------------
  pipeline.component.blend_attachment = blend_attachment;
}
void Component::info_pipeline_blend(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineColorBlendStateCreateInfo blend{};
  blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  blend.logicOpEnable = VK_FALSE;
  blend.logicOp = VK_LOGIC_OP_COPY; // Optional
  blend.attachmentCount = 1;
  blend.pAttachments = &pipeline.component.blend_attachment;
  blend.blendConstants[0] = 0.0f; // Optional
  blend.blendConstants[1] = 0.0f; // Optional
  blend.blendConstants[2] = 0.0f; // Optional
  blend.blendConstants[3] = 0.0f; // Optional

  //---------------------------
  pipeline.component.blend = blend;
}
void Component::info_pipeline_depth_stencil(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineDepthStencilStateCreateInfo stencil;
  stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  stencil.depthTestEnable = (pipeline.shader.info.with_depth_test) ? VK_TRUE : VK_FALSE;
  stencil.depthWriteEnable = (pipeline.shader.info.with_depth_test) ? VK_TRUE : VK_FALSE;
  stencil.depthCompareOp = VK_COMPARE_OP_LESS;
  stencil.depthBoundsTestEnable = VK_FALSE;
  stencil.minDepthBounds = 0.0f; // Optional
  stencil.maxDepthBounds = 1.0f; // Optional
  stencil.stencilTestEnable = VK_FALSE;
  stencil.front = {}; // Optional
  stencil.back = {}; // Optional

  //---------------------------
  pipeline.component.stencil = stencil;
}

//Creation function
void Component::create_pipeline_handle(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline.component.vec_shader_stage.size());
  pipeline_info.pStages = pipeline.component.vec_shader_stage.data();
  pipeline_info.pVertexInputState = &pipeline.component.vertex;
  pipeline_info.pInputAssemblyState = &pipeline.component.topology;
  pipeline_info.pViewportState = &pipeline.component.viewport;
  pipeline_info.pRasterizationState = &pipeline.component.rasterization;
  pipeline_info.pMultisampleState = &pipeline.component.multisample;
  pipeline_info.pDepthStencilState = &pipeline.component.stencil;
  pipeline_info.pColorBlendState = &pipeline.component.blend;
  pipeline_info.pDynamicState = &pipeline.component.dynamic;
  pipeline_info.layout = pipeline.layout;
  pipeline_info.renderPass = renderpass.handle;
  pipeline_info.subpass = pipeline.subpass_ID;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipeline_info.basePipelineIndex = -1; // Optional

  VkResult result = vkCreateGraphicsPipelines(vk_struct->core.device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //---------------------------
}
void Component::clean_pipeline_handle(vk::structure::Pipeline& pipeline){
  //---------------------------

  vkDestroyPipeline(vk_struct->core.device.handle, pipeline.handle, nullptr);

  //---------------------------
}

}
