#include "Pipeline.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_binding = new vk::descriptor::Binding(vk_struct);
  this->vk_shader = new vk::pipeline::Shader(vk_struct);
  this->vk_vertex = new vk::pipeline::Vertex(vk_struct);
  this->vk_object = new vk::pipeline::Object(vk_struct);
  this->vk_layout = new vk::pipeline::Layout(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      this->create_pipeline_struct(renderpass, pipeline);
    }
  }

  //---------------------------
}
void Pipeline::clean_pipeline(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    for(auto& [name, pipeline] : subpass->map_pipeline){
      this->clean_pipeline_struct(pipeline);
    }
  }

  //---------------------------
}

//Pipeline creation / cleaning
void Pipeline::create_pipeline_struct(vk::structure::Renderpass& renderpass, vk::structure::Pipeline* pipeline){
  //---------------------------

  //Pipeline layout & binding
  vk_binding->create_binding(pipeline->binding);
  vk_shader->create_pipeline_shader(pipeline);
  vk_vertex->pipeline_vertex_description(pipeline);
  vk_layout->create_pipeline_layout(pipeline);

  //Pipeline obj
  vk_object->create_pipeline_object(renderpass, pipeline);
  vk_shader->clean_pipeline_shader();

  //---------------------------
}
void Pipeline::clean_pipeline_struct(vk::structure::Pipeline* pipeline){
  //---------------------------

  vk_object->clean_pipeline_handle(pipeline);
  vk_layout->clean_pipeline_layout(pipeline);
  vk_binding->clean_binding(pipeline->binding);

  //---------------------------
}
void Pipeline::cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline){
  //---------------------------

  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->handle);

  //---------------------------
}

}
