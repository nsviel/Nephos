#include "Pipeline.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_shader = new vk::renderpass::Shader(vk_struct);
  this->vk_data = new vk::pipeline::Data(vk_struct);
  this->vk_element = new vk::renderpass::Element(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline(vk::structure::Renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[i];

    for(int j=0; j<subpass->vec_pipeline.size(); j++){
      vk::structure::Pipeline* pipeline = subpass->vec_pipeline[j];
      this->create_pipeline_struct(renderpass, pipeline);
    }
  }

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline){
  //---------------------------

  vkCmdBindPipeline(command_buffer, TYP_BIND_PIPELINE_GRAPHICS, pipeline->pipeline);

  //---------------------------
}
void Pipeline::clean_pipeline(vk::structure::Renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[i];

    for(int j=0; j<subpass->vec_pipeline.size(); j++){
      vk::structure::Pipeline* pipeline = subpass->vec_pipeline[j];
      this->clean_pipeline_struct(pipeline);
    }
  }

  //---------------------------
}

//Pipeline creation / cleaning
void Pipeline::create_pipeline_struct(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  //Pipeline layout & binding
  vk_descriptor->create_binding(&pipeline->binding);
  this->check_struct_pipeline_input(pipeline);
  vk_shader->create_pipeline_shader(pipeline);
  vk_data->pipeline_data_description(pipeline);
  this->create_pipeline_layout(pipeline);

  //Pipeline obj
  vk_element->find_pipeline_element(pipeline);
  this->create_pipeline_obj(renderpass, pipeline);
  this->clean_pipeline_shader_module(pipeline);

  //---------------------------
}
void Pipeline::create_pipeline_obj(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline){
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

  VkResult result = vkCreateGraphicsPipelines(vk_struct->device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline->pipeline);

  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //---------------------------
}
void Pipeline::create_pipeline_layout(vk::structure::Pipeline* pipeline){
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
void Pipeline::clean_pipeline_struct(vk::structure::Pipeline* pipeline){
  //---------------------------

  vkDestroyPipeline(vk_struct->device.handle, pipeline->pipeline, nullptr);
  vkDestroyPipelineLayout(vk_struct->device.handle, pipeline->layout, nullptr);
  vk_descriptor->clean_binding(&pipeline->binding);

  //---------------------------
}
void Pipeline::clean_pipeline_shader_module(vk::structure::Pipeline* pipeline){
  //---------------------------

  for(int i=0; i<pipeline->info.vec_shader_couple.size(); i++){
    std::pair<VkShaderModule, VkShaderModule> shader_couple = pipeline->info.vec_shader_couple[i];
    vkDestroyShaderModule(vk_struct->device.handle, shader_couple.first, nullptr);
    vkDestroyShaderModule(vk_struct->device.handle, shader_couple.second, nullptr);
  }
  pipeline->info.vec_shader_couple.clear();
  pipeline->info.shader_stage.clear();

  //---------------------------
}

//Subfunction
void Pipeline::check_struct_pipeline_input(vk::structure::Pipeline* pipeline){
  //---------------------------

  if(pipeline->definition.name == "") std::cout<<"[error] Pipeline init input -> no name"<<std::endl;
  //if(pipeline->definition.topology == "") std::cout<<"[error] Pipeline init input -> no topology"<<std::endl;
  //if(pipeline->path_shader_vs == "") std::cout<<"[error] Pipeline init input -> no path_shader_vs"<<std::endl;
  //if(pipeline->path_shader_fs == "") std::cout<<"[error] Pipeline init input -> no path_shader_fs"<<std::endl;
  //if(pipeline->definition.vec_data_name.size() == 0) std::cout<<"[error] Pipeline init input -> no vec_data_name"<<std::endl;
  //if(pipeline->binding.vec_required_binding.size() == 0) std::cout<<"[error] Pipeline init input -> no vec_required_binding"<<std::endl;

  //---------------------------
}

}
