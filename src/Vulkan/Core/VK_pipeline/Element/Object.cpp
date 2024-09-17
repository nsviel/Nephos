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
void Object::info_pipeline_topology(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.element.topology = {};
  pipeline.element.topology.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  pipeline.element.topology.primitiveRestartEnable = VK_FALSE;

  switch(pipeline.info.topology){
    case utl::topology::POINT:{
      pipeline.element.topology.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
      break;
    }
    case utl::topology::LINE:{
      pipeline.element.topology.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
      break;
    }
    case utl::topology::TRIANGLE:{
      pipeline.element.topology.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
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
  pipeline.element.dynamic = {};
  pipeline.element.dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  pipeline.element.dynamic.dynamicStateCount = static_cast<uint32_t>(vec_dynamic_state.size());
  pipeline.element.dynamic.pDynamicStates = vec_dynamic_state.data();

  //---------------------------
}
void Object::info_pipeline_viewport(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Viewport info
  pipeline.element.viewport = {};
  pipeline.element.viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  pipeline.element.viewport.viewportCount = 1;
  pipeline.element.viewport.pViewports = &vk_struct->core.viewport.handle;
  pipeline.element.viewport.scissorCount = 1;
  pipeline.element.viewport.pScissors = &vk_struct->core.viewport.scissor;

  //---------------------------
}
void Object::info_pipeline_rasterization(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.element.rasterization = {};
  pipeline.element.rasterization.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  pipeline.element.rasterization.depthClampEnable = VK_FALSE;
  pipeline.element.rasterization.rasterizerDiscardEnable = VK_FALSE;
  pipeline.element.rasterization.polygonMode = VK_POLYGON_MODE_FILL;
  pipeline.element.rasterization.lineWidth = 1.0f;
  pipeline.element.rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
  pipeline.element.rasterization.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  pipeline.element.rasterization.depthBiasEnable = VK_FALSE;
  pipeline.element.rasterization.depthBiasConstantFactor = 0.0f; // Optional
  pipeline.element.rasterization.depthBiasClamp = 0.0f; // Optional
  pipeline.element.rasterization.depthBiasSlopeFactor = 0.0f; // Optional

  //---------------------------
}
void Object::info_pipeline_multisampling(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.element.multisample = {};
  pipeline.element.multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  pipeline.element.multisample.sampleShadingEnable = VK_FALSE;
  pipeline.element.multisample.rasterizationSamples = vk_struct->core.device.physical_device.max_sample_count;
  pipeline.element.multisample.minSampleShading = 1.0f; // Optional
  pipeline.element.multisample.pSampleMask = nullptr; // Optional
  pipeline.element.multisample.alphaToCoverageEnable = VK_FALSE; // Optional
  pipeline.element.multisample.alphaToOneEnable = VK_FALSE; // Optional

  //---------------------------
}
void Object::info_pipeline_blend_attachment(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.element.blend_attachment = {};
  pipeline.element.blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  pipeline.element.blend_attachment.blendEnable = VK_TRUE;
  pipeline.element.blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; // Optional
  pipeline.element.blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; // Optional
  pipeline.element.blend_attachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  pipeline.element.blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  pipeline.element.blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  pipeline.element.blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  //---------------------------
}
void Object::info_pipeline_blend(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.element.blend = {};
  pipeline.element.blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  pipeline.element.blend.logicOpEnable = VK_FALSE;
  pipeline.element.blend.logicOp = VK_LOGIC_OP_COPY; // Optional
  pipeline.element.blend.attachmentCount = 1;
  pipeline.element.blend.pAttachments = &pipeline.element.blend_attachment;
  pipeline.element.blend.blendConstants[0] = 0.0f; // Optional
  pipeline.element.blend.blendConstants[1] = 0.0f; // Optional
  pipeline.element.blend.blendConstants[2] = 0.0f; // Optional
  pipeline.element.blend.blendConstants[3] = 0.0f; // Optional

  //---------------------------
}
void Object::info_pipeline_depth(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.element.stencil = {};
  pipeline.element.stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  pipeline.element.stencil.depthTestEnable = (pipeline.shader.info.with_depth_test) ? VK_TRUE : VK_FALSE;
  pipeline.element.stencil.depthWriteEnable = (pipeline.shader.info.with_depth_test) ? VK_TRUE : VK_FALSE;
  pipeline.element.stencil.depthCompareOp = VK_COMPARE_OP_LESS;
  pipeline.element.stencil.depthBoundsTestEnable = VK_FALSE;
  pipeline.element.stencil.minDepthBounds = 0.0f; // Optional
  pipeline.element.stencil.maxDepthBounds = 1.0f; // Optional
  pipeline.element.stencil.stencilTestEnable = VK_FALSE;
  pipeline.element.stencil.front = {}; // Optional
  pipeline.element.stencil.back = {}; // Optional

  //---------------------------
}

//Creation function
void Object::create_pipeline_handle(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline){
  //---------------------------

  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline.element.vec_shader_stage.size());
  pipeline_info.pStages = pipeline.element.vec_shader_stage.data();
  pipeline_info.pVertexInputState = &pipeline.element.vertex;
  pipeline_info.pInputAssemblyState = &pipeline.element.topology;
  pipeline_info.pViewportState = &pipeline.element.viewport;
  pipeline_info.pRasterizationState = &pipeline.element.rasterization;
  pipeline_info.pMultisampleState = &pipeline.element.multisample;
  pipeline_info.pDepthStencilState = &pipeline.element.stencil;
  pipeline_info.pColorBlendState = &pipeline.element.blend;
  pipeline_info.pDynamicState = &pipeline.element.dynamic;
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
