#include "Component.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline::compute{

//Constructor / Destructor
Component::Component(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = new vk::shader::Module(vk_struct);
  this->vk_layout = new vk::pipeline::Layout(vk_struct);

  //---------------------------
}
Component::~Component(){}

//Main function
void Component::create_pipeline_component(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Pipeline attribut description
  vk_shader->create_pipeline_module(pipeline);
  vk_layout->create_pipeline_layout(pipeline);

  //Pipeline creation
  this->create_pipeline_handle(pipeline);
  vk_shader->clean_pipeline_module(pipeline);

  //---------------------------
}
void Component::clean_pipeline_component(vk::structure::Pipeline& pipeline){
  //---------------------------

  this->clean_pipeline_handle(pipeline);
  vk_layout->clean_pipeline_layout(pipeline);

  //---------------------------
}

//Creation function
void Component::create_pipeline_handle(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkComputePipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
  pipeline_info.stage = pipeline.component.vec_shader_stage[0];
  pipeline_info.layout = pipeline.layout;

  VkResult result = vkCreateComputePipelines(vk_struct->core.device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline.handle);
  if(result != VK_SUCCESS){
    std::cout<<"[error] failed to create compute pipeline"<<std::endl;
  }

  //---------------------------
}
void Component::clean_pipeline_handle(vk::structure::Pipeline& pipeline){
  //---------------------------

  vkDestroyPipeline(vk_struct->core.device.handle, pipeline.handle, nullptr);

  //---------------------------
}

}
