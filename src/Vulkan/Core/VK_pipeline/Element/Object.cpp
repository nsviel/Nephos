#include "Object.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Object::Object(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::create_pipeline_object(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  this->info_pipeline_vertex(pipeline);
  this->info_pipeline_topology(pipeline);
  this->info_pipeline_dynamic(pipeline);
  this->info_pipeline_viewport(pipeline);
  this->info_pipeline_rasterization(pipeline);
  this->info_pipeline_multisampling(pipeline);
  this->info_pipeline_blend_attachment(pipeline);
  this->info_pipeline_blend(pipeline);
  this->info_pipeline_depth(pipeline);
  this->create_pipeline_handle(renderpass, pipeline);

  //---------------------------
}

//Subfunction
void Object::info_pipeline_vertex(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_vertex = {};
  info_vertex.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  info_vertex.vertexBindingDescriptionCount = static_cast<uint32_t>(pipeline.element.vec_vertex_binding.size());
  info_vertex.vertexAttributeDescriptionCount = static_cast<uint32_t>(pipeline.element.vec_attribut_info.size());
  info_vertex.pVertexBindingDescriptions = pipeline.element.vec_vertex_binding.data();
  info_vertex.pVertexAttributeDescriptions = pipeline.element.vec_attribut_info.data();

  //---------------------------
}
void Object::info_pipeline_topology(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_topology = {};
  info_topology.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  info_topology.primitiveRestartEnable = VK_FALSE;

  switch(pipeline.info.topology){
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
void Object::info_pipeline_dynamic(vk::structure::Pipeline& pipeline){
  //---------------------------

  std::vector<VkDynamicState>& vec_dynamic_state = pipeline.element.vec_dynamic_state;
  vec_dynamic_state.clear();
  vec_dynamic_state.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  vec_dynamic_state.push_back(VK_DYNAMIC_STATE_SCISSOR);
  vec_dynamic_state.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);

  //Dynamic internal variables (viewport, line width, ...)
  info_dynamic = {};
  info_dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  info_dynamic.dynamicStateCount = static_cast<uint32_t>(vec_dynamic_state.size());
  info_dynamic.pDynamicStates = vec_dynamic_state.data();

  //---------------------------
}
void Object::info_pipeline_viewport(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Viewport info
  info_viewport = {};
  info_viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  info_viewport.viewportCount = 1;
  info_viewport.pViewports = &vk_struct->core.viewport.handle;
  info_viewport.scissorCount = 1;
  info_viewport.pScissors = &vk_struct->core.viewport.scissor;

  //---------------------------
}
void Object::info_pipeline_rasterization(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_rasterization = {};
  info_rasterization.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  info_rasterization.depthClampEnable = VK_FALSE;
  info_rasterization.rasterizerDiscardEnable = VK_FALSE;
  info_rasterization.polygonMode = VK_POLYGON_MODE_FILL;
  info_rasterization.lineWidth = 1.0f;
  info_rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
  info_rasterization.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  info_rasterization.depthBiasEnable = VK_FALSE;
  info_rasterization.depthBiasConstantFactor = 0.0f; // Optional
  info_rasterization.depthBiasClamp = 0.0f; // Optional
  info_rasterization.depthBiasSlopeFactor = 0.0f; // Optional

  //---------------------------
}
void Object::info_pipeline_multisampling(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_multisample = {};
  info_multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  info_multisample.sampleShadingEnable = VK_FALSE;
  info_multisample.rasterizationSamples = vk_struct->core.device.physical_device.max_sample_count;
  info_multisample.minSampleShading = 1.0f; // Optional
  info_multisample.pSampleMask = nullptr; // Optional
  info_multisample.alphaToCoverageEnable = VK_FALSE; // Optional
  info_multisample.alphaToOneEnable = VK_FALSE; // Optional

  //---------------------------
}
void Object::info_pipeline_blend_attachment(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_blend_attachment = {};
  info_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  info_blend_attachment.blendEnable = VK_TRUE;
  info_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; // Optional
  info_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; // Optional
  info_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  info_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  info_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  info_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  //---------------------------
}
void Object::info_pipeline_blend(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_blend = {};
  info_blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  info_blend.logicOpEnable = VK_FALSE;
  info_blend.logicOp = VK_LOGIC_OP_COPY; // Optional
  info_blend.attachmentCount = 1;
  info_blend.pAttachments = &info_blend_attachment;
  info_blend.blendConstants[0] = 0.0f; // Optional
  info_blend.blendConstants[1] = 0.0f; // Optional
  info_blend.blendConstants[2] = 0.0f; // Optional
  info_blend.blendConstants[3] = 0.0f; // Optional

  //---------------------------
}
void Object::info_pipeline_depth(vk::structure::Pipeline& pipeline){
  //---------------------------

  info_stencil = {};
  info_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  info_stencil.depthTestEnable = (pipeline.shader.with_depth_test) ? VK_TRUE : VK_FALSE;
  info_stencil.depthWriteEnable = (pipeline.shader.with_depth_test) ? VK_TRUE : VK_FALSE;
  info_stencil.depthCompareOp = VK_COMPARE_OP_LESS;
  info_stencil.depthBoundsTestEnable = VK_FALSE;
  info_stencil.minDepthBounds = 0.0f; // Optional
  info_stencil.maxDepthBounds = 1.0f; // Optional
  info_stencil.stencilTestEnable = VK_FALSE;
  info_stencil.front = {}; // Optional
  info_stencil.back = {}; // Optional

  //---------------------------
}

//Creation function
void Object::create_pipeline_handle(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline.element.vec_shader_stage.size());
  pipeline_info.pStages = pipeline.element.vec_shader_stage.data();
  pipeline_info.pVertexInputState = &info_vertex;
  pipeline_info.pInputAssemblyState = &info_topology;
  pipeline_info.pViewportState = &info_viewport;
  pipeline_info.pRasterizationState = &info_rasterization;
  pipeline_info.pMultisampleState = &info_multisample;
  pipeline_info.pDepthStencilState = &info_stencil;
  pipeline_info.pColorBlendState = &info_blend;
  pipeline_info.pDynamicState = &info_dynamic;
  pipeline_info.layout = pipeline.layout;
  pipeline_info.renderPass = renderpass.handle;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipeline_info.basePipelineIndex = -1; // Optional

  VkResult result = vkCreateGraphicsPipelines(vk_struct->core.device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline.handle);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //---------------------------
}
void Object::clean_pipeline_handle(vk::structure::Pipeline& pipeline){
  //---------------------------

  vkDestroyPipeline(vk_struct->core.device.handle, pipeline.handle, nullptr);

  //---------------------------
}

}
