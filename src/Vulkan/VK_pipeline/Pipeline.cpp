#include "Pipeline.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_descriptor = new vk::binding::Descriptor(vk_struct);
  this->vk_shader = new vk::pipeline::Shader(vk_struct);
  this->vk_data = new vk::pipeline::Data(vk_struct);
  this->vk_element = new vk::pipeline::Element(vk_struct);
  this->vk_layout = new vk::pipeline::Layout(vk_struct);

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
  vk_shader->create_pipeline_shader(pipeline);
  vk_data->pipeline_data_description(pipeline);
  vk_layout->create_pipeline_layout(pipeline);

  //Pipeline obj
  vk_element->find_pipeline_element(pipeline);
  vk_layout->create_pipeline_handle(renderpass, pipeline);
  vk_shader->clean_pipeline_shader(pipeline);

  //---------------------------
}
void Pipeline::clean_pipeline_struct(vk::structure::Pipeline* pipeline){
  //---------------------------

  vk_layout->clean_pipeline_handle(pipeline);
  vk_layout->clean_pipeline_layout(pipeline);
  vk_descriptor->clean_binding(&pipeline->binding);

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline){
  //---------------------------

  vkCmdBindPipeline(command_buffer, TYP_BIND_PIPELINE_GRAPHICS, pipeline->handle);

  //---------------------------
}

}
